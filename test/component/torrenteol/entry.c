/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/torrenteol/entry.c
 *
 * Purpose: Component-test the skeleton against a temporary text file that
 *          contains LF, CRLF, and CR. The file is the fixture the line
 *          reader will consume; this skeleton only checks that the fixture
 *          can be created and that init/uninit still succeed beside it.
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

static char const fixture_bytes[] = "alpha\nbeta\r\ngamma\rdelta";


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void TEST_FIXTURE_FILE_CONTAINS_LF_CRLF_AND_CR(void);
static void TEST_torrenteol_init_WHILE_FIXTURE_FILE_IS_OPEN(void);


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.torrenteol", verbosity))
    {
        XTESTS_RUN_CASE(TEST_FIXTURE_FILE_CONTAINS_LF_CRLF_AND_CR);
        XTESTS_RUN_CASE(TEST_torrenteol_init_WHILE_FIXTURE_FILE_IS_OPEN);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void TEST_FIXTURE_FILE_CONTAINS_LF_CRLF_AND_CR(void)
{
    FILE*       f = tmpfile();
    char        buf[64];
    size_t      n;
    size_t      wrote;
    size_t      got;

    TEST_PTR_NE(NULL, f);

    if (NULL == f)
    {
        return;
    }

    n = sizeof(fixture_bytes) - 1;
    wrote = fwrite(fixture_bytes, 1, n, f);

    TEST_INT_EQ((int)n, (int)wrote);

    rewind(f);

    got = fread(buf, 1, sizeof(buf), f);

    TEST_INT_EQ((int)n, (int)got);
    TEST_INT_EQ(0, memcmp(fixture_bytes, buf, n));

    fclose(f);
}

static void TEST_torrenteol_init_WHILE_FIXTURE_FILE_IS_OPEN(void)
{
    FILE* f = tmpfile();

    TEST_PTR_NE(NULL, f);

    if (NULL == f)
    {
        return;
    }

    TEST_INT_EQ((int)(sizeof(fixture_bytes) - 1), (int)fwrite(fixture_bytes, 1, sizeof(fixture_bytes) - 1, f));
    TEST_INT_EQ(TORRENTEOL_RC_SUCCESS, torrenteol_init());
    TEST_INT_EQ((int)TORRENTEOL_VER, (int)torrenteol_getVersion());
    TEST_INT_EQ(TORRENTEOL_RC_SUCCESS, torrenteol_uninit());

    fclose(f);
}


/* ///////////////////////////// end of file //////////////////////////// */

