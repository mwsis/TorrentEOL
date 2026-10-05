/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/c/init/main.c
 *
 * Purpose: Minimal illustration of torrenteol_init(),
 *          torrenteol_getVersion(), and torrenteol_uninit().
 *
 * Created: 5th October 2026
 * Updated: 5th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <torrenteol/torrenteol.h>

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
    TORRENTEOL_RC   rc;
    uint32_t        ver;

    ((void)&argc);
    ((void)&argv);

    rc = torrenteol_init();

    if (TORRENTEOL_RC_SUCCESS != rc)
    {
        fprintf(stderr, "torrenteol_init() failed: %d\n", (int)rc);

        return EXIT_FAILURE;
    }

    ver = torrenteol_getVersion();

    printf(
        "TorrentEOL %u.%u.%u (0x%08x)\n"
    ,   (unsigned)((ver >> 24) & 0xff)
    ,   (unsigned)((ver >> 16) & 0xff)
    ,   (unsigned)((ver >> 8) & 0xff)
    ,   (unsigned)ver
    );

    rc = torrenteol_uninit();

    if (TORRENTEOL_RC_SUCCESS != rc)
    {
        fprintf(stderr, "torrenteol_uninit() failed: %d\n", (int)rc);

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

