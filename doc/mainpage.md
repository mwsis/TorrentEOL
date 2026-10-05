# torrenteol {#mainpage}

**TorrentEOL** is a C library for the fastest practical reading of text-file
lines: LF, CRLF, and CR, into a caller-supplied block or an allocated line.

This release is the skeleton. The public API is initialisation and version.


## Components

| Module | Header | Summary |
| ------ | ------ | ------- |
| @ref group__torrenteol_api | `<torrenteol/torrenteol.h>` | `torrenteol_init()`, `torrenteol_uninit()`, `torrenteol_getVersion()` |


## Quick start

```c
#include <torrenteol/torrenteol.h>

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    TORRENTEOL_RC rc = torrenteol_init();

    if (TORRENTEOL_RC_SUCCESS != rc)
    {
        return EXIT_FAILURE;
    }

    printf("0x%08x\n", (unsigned)torrenteol_getVersion());

    torrenteol_uninit();

    return EXIT_SUCCESS;
}
```

Consumer **CMake** projects may use `find_package(torrenteol)` and link
`torrenteol::core`. See
[INSTALL.md](https://github.com/synesissoftware/torrenteol/blob/master/INSTALL.md)
for build and install instructions.


## Related projects

* [cstring](https://github.com/synesissoftware/cstring)


<!-- ########################### end of file ########################### -->
