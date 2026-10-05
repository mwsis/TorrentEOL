# torrenteol - Installation and Use <!-- omit in toc -->

**TorrentEOL** is a classic-form C library, insofar as it has implementation
files in its **src** directory and header files in its **include/torrenteol**
directory. Thus, once "installed", one must simply include
**torrenteol/torrenteol.h**, and compile-in or link-in the implementation.

The **C** API has no non-standard dependencies. Building the project's tests
additionally requires **STLSoft** and **xTests** (and optionally recognises
**p99** for performance percentiles and **shwild** for enhanced xTests
match constructs). C++ performance tests may be omitted with
`--no-cpp` / `NO_TORRENTEOL_CPP_API`; the **C** unit-tests and component
tests still require **STLSoft** and **xTests** unless testing is disabled.


## Table of Contents <!-- omit in toc -->

- [CMake](#cmake)
- [Bundled](#bundled)


## CMake

The primary choice for installation is by use of **CMake**.

1. Obtain the latest distribution of **torrenteol**, from
   https://github.com/synesissoftware/torrenteol/, e.g.

   ```bash
   $ mkdir -p ~/open-source
   $ cd ~/open-source
   $ git clone https://github.com/synesissoftware/torrenteol/
   ```

2. Prepare the CMake configuration, via the **prepare_cmake.sh** script.

   For a minimal library install (no **STLSoft** / **xTests** required):

   ```bash
   $ cd ~/open-source/torrenteol
   $ ./prepare_cmake.sh --no-cpp --disable-testing -v
   ```

   For a full build including examples and tests, install **STLSoft** 1.11
   (and **xTests** for tests) via their own **CMake** scripts first, then:

   ```bash
   $ cd ~/open-source/torrenteol
   $ ./prepare_cmake.sh -v
   ```

3. Build, via **build_cmake.sh** (or `cmake --build`).

4. Install, via `cmake --install`, into a prefix of your choosing.

A consuming project then does:

```cmake
find_package(torrenteol REQUIRED)
target_link_libraries(app PRIVATE torrenteol::core)
```


## Bundled

The library may also be compiled directly from **src/torrenteol.core.c** with
**include/** on the include path. That path does not produce the CMake
package.


<!-- ########################### end of file ########################### -->
