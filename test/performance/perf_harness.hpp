/* /////////////////////////////////////////////////////////////////////////
 * File:    test/performance/perf_harness.hpp
 *
 * Purpose: Shared helpers for TorrentEOL performance programs.
 *
 * Created: 5th October 2026
 * Updated: 5th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#ifndef TORRENTEOL_TEST_PERFORMANCE_PERF_HARNESS_HPP_INCLUDED
#define TORRENTEOL_TEST_PERFORMANCE_PERF_HARNESS_HPP_INCLUDED


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <platformstl/system/console_functions.h>
#include <stlsoft/conversion/number/grouping_functions.hpp>
#include <stlsoft/diagnostics/std_chrono_hrc_stopwatch.hpp>
#include <stlsoft/std/cstdlib.hpp>
#include <stlsoft/stlsoft.h>

#ifdef HAS_P99
# include <p99/p99.hpp>
#endif

#include <iomanip>
#include <iostream>
#include <string>

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

typedef stlsoft::std_chrono_hrc_stopwatch                   stopwatch_t;
typedef stopwatch_t::interval_type                          interval_t;


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

namespace torrenteol_perf
{


/* /////////////////////////////////////////////////////////////////////////
 * configuration
 */

inline
size_t
env_size_t(
    char const* name
,   size_t      default_value
)
{
    char const* const env = ::getenv(name);

    if (NULL == env ||
        '\0' == env[0])
    {
        return default_value;
    }

    char*               end =   NULL;
    unsigned long const v   =   stlsoft::strtoul(env, &end, 10);

    if (NULL == end ||
        '\0' != *end)
    {
        return default_value;
    }

    return static_cast<size_t>(v);
}

inline
size_t
default_iterations()
{
#ifdef NDEBUG

    return env_size_t("TORRENTEOL_PERF_ITERATIONS", 100000u);
#else

    return env_size_t("TORRENTEOL_PERF_ITERATIONS", 1000u);
#endif
}

inline
size_t
default_warmups()
{
    return env_size_t("TORRENTEOL_PERF_WARMUPS", 2u);
}


/* /////////////////////////////////////////////////////////////////////////
 * timing
 */

struct run_result
{
    interval_t      tm_ns;
    std::uint64_t   anchor;
#ifdef HAS_P99

    p99::histogram  hist;
#endif /* HAS_P99 */
};

/* tm_ns is one start/stop around the iteration loop. When p99 is linked,
 * the last warmup also times each call into the histogram. Those samples
 * are the percentiles only.
 */
template <typename F>
run_result
time_iterations(
    size_t  num_iterations
,   size_t  num_warm_loops
,   F       fn
)
{
    run_result  result = {};
    stopwatch_t sw;

    if (0 == num_warm_loops)
    {
        num_warm_loops = 1;
    }

    for (size_t w = num_warm_loops; 0 != w; --w)
    {
        result.anchor = 0;
#ifdef HAS_P99

        result.hist.clear();
#endif /* HAS_P99 */

        sw.start();

        for (size_t i = 0; num_iterations != i; ++i)
        {
            result.anchor += fn();
        }

        sw.stop();

        interval_t const tm_ns = sw.get_nanoseconds();

#ifdef HAS_P99

        if (1 == w)
        {
            std::uint64_t volatile hist_anchor = 0;

            for (size_t i = 0; num_iterations != i; ++i)
            {
                sw.start();
                hist_anchor += fn();
                sw.stop();

                interval_t const sample = sw.get_nanoseconds();

                (void)result.hist.push_ns(static_cast<std::uint64_t>(sample));
            }

            (void)hist_anchor;
        }
#endif /* HAS_P99 */

        if (1 == w)
        {
            result.tm_ns = tm_ns;
        }
    }

    return result;
}


/* /////////////////////////////////////////////////////////////////////////
 * display
 */

template <ss_typename_param_k T_integer>
inline
std::string
thousands(
    T_integer const& v
)
{
    char    dest[41];
    size_t  n = stlsoft::format_thousands(dest, STLSOFT_NUM_ELEMENTS(dest), "3;0", v);

    return std::string(dest, n > 0 ? n - 1 : 0);
}

inline
void
display_banner(
    char const* program_name
)
{
    std::cout
        << program_name
        << ": performance timings (human attention; not a CI gate)."
        << std::endl
        << "  Skeleton times torrenteol_getVersion() and init/uninit."
        << std::endl
        << "  Prefer Release builds."
        << std::endl
#ifdef HAS_P99
        << "  p99: p50/p90/p99/max are one iteration, not divided by #acts."
        << std::endl
        << "  ns/op is one start/stop around the loop, then divided by #acts."
        << std::endl
        << "  Env: TORRENTEOL_PERF_ITERATIONS, TORRENTEOL_PERF_WARMUPS"
        << ", SIS_PERFTESTS_GROUPGAPS."
#else /* ? HAS_P99 */
        << "  p99: not linked — mean ns/op only."
        << std::endl
        << "  Env: TORRENTEOL_PERF_ITERATIONS, TORRENTEOL_PERF_WARMUPS"
        << ", SIS_PERFTESTS_GROUPGAPS."
#endif /* HAS_P99 */
        << std::endl
        ;
}

#ifdef HAS_P99

inline
void
append_percentile_columns(
    p99::histogram const*   h
)
{
    uint64_t p50 = 0;
    uint64_t p90 = 0;
    uint64_t p99v = 0;
    uint64_t maxv = 0;

    if (NULL != h && !h->empty())
    {
        (void)h->try_get_value_at_p50(&p50);
        (void)h->try_get_value_at_percentile(90.0, &p90);
        (void)h->try_get_value_at_p99(&p99v);
        (void)h->try_get_max_event_time(&maxv);
    }

    std::cout
        << '\t' << std::setw(10) << std::right << thousands(p50)
        << '\t' << std::setw(10) << std::right << thousands(p90)
        << '\t' << std::setw(10) << std::right << thousands(p99v)
        << '\t' << std::setw(10) << std::right << thousands(maxv)
        ;
}
#endif /* HAS_P99 */

inline
bool
env_is_truey(
    char const* name
)
{
    char const* const env = ::getenv(name);

    if (NULL == env ||
        '\0' == env[0])
    {
        return false;
    }

    if (0 == ::strcmp(env, "1") ||
        0 == ::strcmp(env, "ok") ||
        0 == ::strcmp(env, "on") ||
        0 == ::strcmp(env, "true") ||
        0 == ::strcmp(env, "yes") ||
        0 == ::strcmp(env, "y") ||
        0 == ::strcmp(env, "OK") ||
        0 == ::strcmp(env, "ON") ||
        0 == ::strcmp(env, "TRUE") ||
        0 == ::strcmp(env, "YES") ||
        0 == ::strcmp(env, "Y"))
    {
        return true;
    }

    return false;
}

inline
bool
group_gaps_enabled()
{
    return env_is_truey("SIS_PERFTESTS_GROUPGAPS");
}

inline
void
maybe_emit_group_gap(
    char const* scenario
)
{
    if (!group_gaps_enabled())
    {
        return;
    }

    static bool         have_prev = false;
    static std::string  prev_scenario;

    if (have_prev &&
        prev_scenario != scenario)
    {
        if (platformstl::isatty(stdout))
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\t----------" << std::endl;
        }
    }

    prev_scenario   =   scenario;
    have_prev       =   true;
}

inline
void
display_results_title()
{
    std::cout
        << '\t'
        << std::setw(40) << std::left << "scenario"
        << '\t'
        << std::setw(24) << std::left << "impl"
        << '\t'
        << std::setw(12) << std::right << "#iters"
        << '\t'
        << std::setw(14) << std::right << "tm (ns)"
        << '\t'
        << std::setw(12) << std::right << "ns/op"
#ifdef HAS_P99
        << '\t'
        << std::setw(10) << std::right << "p50/iter"
        << '\t'
        << std::setw(10) << std::right << "p90/iter"
        << '\t'
        << std::setw(10) << std::right << "p99/iter"
        << '\t'
        << std::setw(10) << std::right << "max/iter"
#endif /* HAS_P99 */
        << '\t'
        << std::setw(14) << std::right << "anchor"
        << std::endl
        ;
}

inline
void
display_results(
    char const*             scenario
,   char const*             impl
,   size_t                  num_iterations
,   run_result const&       result
)
{
    maybe_emit_group_gap(scenario);

    size_t const denom = (0 == num_iterations) ? 1u : num_iterations;

    std::cout
        << '\t'
        << std::setw(40) << std::left << scenario
        << '\t'
        << std::setw(24) << std::left << impl
        << '\t'
        << std::setw(12) << std::right << num_iterations
        << '\t'
        << std::setw(14) << std::right << thousands(result.tm_ns)
        << '\t'
        << std::setw(12) << std::right << thousands(result.tm_ns / denom)
#ifdef HAS_P99
        ;
    append_percentile_columns(&result.hist);
    std::cout
#endif /* HAS_P99 */
        << '\t'
        << std::setw(14) << std::right << result.anchor
        << std::endl
        ;
}

} /* namespace torrenteol_perf */


/* ////////////////////////////////////////////////////////////////////// */

#endif /* !TORRENTEOL_TEST_PERFORMANCE_PERF_HARNESS_HPP_INCLUDED */

/* ///////////////////////////// end of file //////////////////////////// */

