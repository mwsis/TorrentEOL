/* /////////////////////////////////////////////////////////////////////////
 * File:    test/performance/torrenteol/main.cpp
 *
 * Purpose: Times torrenteol_getVersion() and an init/uninit pair. Human
 *          attention only; not a CTest gate.
 *
 * Created: 5th October 2026
 * Updated: 5th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <torrenteol/torrenteol.h>

#include "../perf_harness.hpp"

#include <stdint.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
    size_t const iterations = torrenteol_perf::default_iterations();
    size_t const warmups    = torrenteol_perf::default_warmups();

    ((void)argc);
    ((void)argv);

    torrenteol_perf::display_banner("test.performance.torrenteol");
    torrenteol_perf::display_results_title();

    {
        torrenteol_perf::run_result const result = torrenteol_perf::time_iterations(
            iterations
        ,   warmups
        ,   []() -> std::uint64_t
            {
                return torrenteol_getVersion();
            }
        );

        torrenteol_perf::display_results(
            "getVersion"
        ,   "torrenteol_getVersion"
        ,   iterations
        ,   result
        );
    }

    {
        torrenteol_perf::run_result const result = torrenteol_perf::time_iterations(
            iterations
        ,   warmups
        ,   []() -> std::uint64_t
            {
                TORRENTEOL_RC const rc_init     =   torrenteol_init();
                TORRENTEOL_RC const rc_uninit   =   torrenteol_uninit();

                return (std::uint64_t)rc_init + (std::uint64_t)rc_uninit;
            }
        );

        torrenteol_perf::display_results(
            "init/uninit"
        ,   "torrenteol_init+uninit"
        ,   iterations
        ,   result
        );
    }

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

