/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/torrenteol/entry.c
 *
 * Purpose: Unit-tests torrenteol_getVersion(), torrenteol_init(), and
 *          torrenteol_uninit().
 *
 * Created: 5th October 2026
 * Updated: 5th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <torrenteol/torrenteol.h>

#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void TEST_torrenteol_getVersion_MATCHES_TORRENTEOL_VER(void);
static void TEST_torrenteol_uninit_WHEN_NOT_INITIALISED(void);
static void TEST_torrenteol_init_THEN_uninit(void);
static void TEST_torrenteol_init_WHEN_ALREADY_INITIALISED(void);


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.torrenteol", verbosity))
    {
        XTESTS_RUN_CASE(TEST_torrenteol_getVersion_MATCHES_TORRENTEOL_VER);
        XTESTS_RUN_CASE(TEST_torrenteol_uninit_WHEN_NOT_INITIALISED);
        XTESTS_RUN_CASE(TEST_torrenteol_init_THEN_uninit);
        XTESTS_RUN_CASE(TEST_torrenteol_init_WHEN_ALREADY_INITIALISED);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void TEST_torrenteol_getVersion_MATCHES_TORRENTEOL_VER(void)
{
    uint32_t const ver = torrenteol_getVersion();

    TEST_INT_EQ((int)TORRENTEOL_VER, (int)ver);
    TEST_INT_EQ(TORRENTEOL_VER_MAJOR, (int)((ver >> 24) & 0xff));
    TEST_INT_EQ(TORRENTEOL_VER_MINOR, (int)((ver >> 16) & 0xff));
    TEST_INT_EQ(TORRENTEOL_VER_PATCH, (int)((ver >> 8) & 0xff));
    TEST_INT_EQ(TORRENTEOL_VER_ALPHABETA, (int)((ver >> 0) & 0xff));
}

static void TEST_torrenteol_uninit_WHEN_NOT_INITIALISED(void)
{
    TEST_INT_EQ(TORRENTEOL_RC_NOT_INITIALISED, torrenteol_uninit());
}

static void TEST_torrenteol_init_THEN_uninit(void)
{
    TEST_INT_EQ(TORRENTEOL_RC_SUCCESS, torrenteol_init());
    TEST_INT_EQ(TORRENTEOL_RC_SUCCESS, torrenteol_uninit());
    TEST_INT_EQ(TORRENTEOL_RC_NOT_INITIALISED, torrenteol_uninit());
}

static void TEST_torrenteol_init_WHEN_ALREADY_INITIALISED(void)
{
    TEST_INT_EQ(TORRENTEOL_RC_SUCCESS, torrenteol_init());
    TEST_INT_EQ(TORRENTEOL_RC_ALREADY_INITIALISED, torrenteol_init());
    TEST_INT_EQ(TORRENTEOL_RC_SUCCESS, torrenteol_uninit());
}


/* ///////////////////////////// end of file //////////////////////////// */

