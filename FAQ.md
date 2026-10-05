# torrenteol - FAQ <!-- omit in toc -->

The FAQ list is under (constant) development. If you post a question on the
Issues forum (https://github.com/synesissoftware/torrenteol/issues)
it will be used to create one.


## Table of Contents <!-- omit in toc -->

- [Q1: "How do I build TorrentEOL?"](#q1-how-do-i-build-torrenteol)
- [Q2: "How do I install TorrentEOL?"](#q2-how-do-i-install-torrenteol)
- [Q3: "How do I use TorrentEOL?"](#q3-how-do-i-use-torrenteol)
- [Q4: "Does TorrentEOL have its own unit-tests?"](#q4-does-torrenteol-have-its-own-unit-tests)
- [Q5: "How do I build without the C++ performance tests?"](#q5-how-do-i-build-without-the-c-performance-tests)
- [Q6: "Where are the examples?"](#q6-where-are-the-examples)


# FAQs: <!-- omit in toc -->


## Q1: "How do I build TorrentEOL?"

See [INSTALL.md](./INSTALL.md) for the recommended **CMake** flow
(**prepare_cmake.sh**, then **build_cmake.sh**).

For a minimal library install with no external dependencies:

```bash
$ ./prepare_cmake.sh --no-cpp --disable-testing -m
```

For a full build including examples and tests, install **STLSoft** 1.11 and
**xTests** first, then:

```bash
$ ./prepare_cmake.sh -m
```

Execute `$ ./prepare_cmake.sh --help` for the full set of options.


## Q2: "How do I install TorrentEOL?"

Configure, build, and install with **CMake**. After installation, consumers
use `find_package(torrenteol)` and link `torrenteol::core`. See
[INSTALL.md](./INSTALL.md).


## Q3: "How do I use TorrentEOL?"

Include `<torrenteol/torrenteol.h>`. Call `torrenteol_init()`, then
`torrenteol_getVersion()` if you need the loaded version, then
`torrenteol_uninit()`. Line reading is not in this skeleton.


## Q4: "Does TorrentEOL have its own unit-tests?"

Yes. **test.unit.torrenteol** covers the three API functions.
**test.component.torrenteol** creates a temporary file containing LF, CRLF,
and CR. **test.performance.torrenteol** times `torrenteol_getVersion()` and
an init/uninit pair; it is for human attention and is not a CTest gate.

Run them with **run_all_unit_tests.sh**, **run_all_component_tests.sh**, and
**run_all_performance_tests.sh**.


## Q5: "How do I build without the C++ performance tests?"

```bash
$ ./prepare_cmake.sh --no-cpp
```

That sets `NO_TORRENTEOL_CPP_API=ON`. The C unit-tests and component tests
still require **STLSoft** and **xTests** unless testing is disabled.


## Q6: "Where are the examples?"

Under **examples/**. See [examples/c/init](./examples/c/init/).


<!-- ########################### end of file ########################### -->
