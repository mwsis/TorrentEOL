# example.c.init <!-- omit in toc -->


## Purpose

Minimal illustration of `torrenteol_init()`, `torrenteol_getVersion()`, and `torrenteol_uninit()`.


## Build

Built when `BUILD_EXAMPLES` is enabled (the default).


## Run

```sh
${SIS_CMAKE_BUILD_DIR:-./_build}/examples/c/init/example.c.init
```


## Expected output

```
TorrentEOL 0.1.0 (0x00010041)
```

The parenthesised value is `TORRENTEOL_VER`. The alphabeta byte (`0x41`) is alpha 1 and is not printed in the dotted triple.


<!-- ########################### end of file ########################### -->
