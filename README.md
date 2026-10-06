# TorrentEOL <!-- omit in toc -->

TorrentEOL: A torrential stream of line parsing.


![C](https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white)
[![License](https://img.shields.io/badge/License-BSD_3--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
[![GitHub release](https://img.shields.io/github/v/release/synesissoftware/torrenteol.svg)](https://github.com/synesissoftware/torrenteol/releases/latest)
[![Last Commit](https://img.shields.io/github/last-commit/synesissoftware/torrenteol)](https://github.com/synesissoftware/torrenteol/commits/master)
[![CI](https://github.com/synesissoftware/torrenteol/actions/workflows/ci.yml/badge.svg)](https://github.com/synesissoftware/torrenteol/actions/workflows/ci.yml)


## Table of Contents <!-- omit in toc -->

- [Introduction](#introduction)
- [Usage](#usage)
- [Installation](#installation)
- [Components](#components)
- [Examples](#examples)
- [Project Information](#project-information)
  - [Where to get help](#where-to-get-help)
  - [Contribution guidelines](#contribution-guidelines)
  - [Dependencies](#dependencies)
  - [Related projects](#related-projects)
  - [License](#license)


## Introduction

**TorrentEOL** is a C library for the fastest-practical flexible reading of text-file lines. It will recognise LF, CRLF, and CR as one terminator each, and it will be able to fill a caller-supplied block or allocate and return a line.

This tree is the skeleton. The public API is `torrenteol_init()`, `torrenteol_uninit()`, and `torrenteol_getVersion()`. Line reading is not implemented yet.

The **C** API has no non-standard dependencies. Building tests requires **STLSoft** and **xTests** (and may optionally recognise **shwild** and **p99**).


## Usage

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


## Installation

See [INSTALL.md](./INSTALL.md).


## Components

| Construct | Header | Summary |
| --------- | ------ | ------- |
| `torrenteol_getVersion()` | `<torrenteol/torrenteol.h>` | Composite version of the loaded library |
| `torrenteol_init()` | `<torrenteol/torrenteol.h>` | Initialises the library |
| `torrenteol_uninit()` | `<torrenteol/torrenteol.h>` | Uninitialises the library |
| `TORRENTEOL_RC` | `<torrenteol/torrenteol.h>` | Return codes for init and uninit |
| `TORRENTEOL_VER` | `<torrenteol/torrenteol.h>` | Composite version macro |


## Examples

Examples live under **examples/**. The directory is the subject; the built program is `example.<lang>.<subject>`. Build them with `BUILD_EXAMPLES` (on by default); run via **run_all_examples.sh**.

| Example | Language | Notes |
| ------- | -------- | ----- |
| [**example.c.init**](./examples/c/init/) | C | `torrenteol_init()`, `torrenteol_getVersion()`, `torrenteol_uninit()` |


## Project Information


### Where to get help

* [GitHub Page](https://github.com/synesissoftware/torrenteol)
* [GitHub Issues](https://github.com/synesissoftware/torrenteol/issues)
* [FAQ.md](./FAQ.md)
* [HOW_YOU_CAN_HELP.md](./HOW_YOU_CAN_HELP.md)


### Contribution guidelines

Defect reports, feature requests, and pull requests are welcome on https://github.com/synesissoftware/torrenteol.

See also [HOW_YOU_CAN_HELP.md](./HOW_YOU_CAN_HELP.md).


### Dependencies

The **C** API has no non-standard dependencies.

| Dependency | Role | Required? |
| ---------- | ---- | --------- |
| [**STLSoft**](https://github.com/synesissoftware/STLSoft) 1.11 | Test headers | ⚪ Tests only (`BUILD_TESTING`) |
| [**xTests**](https://github.com/synesissoftware/xTests) (≥ 0.26) | Unit / component / scratch tests | ⚪ Tests only (`BUILD_TESTING`) |
| [**p99**](https://github.com/synesissoftware/p99) | Percentiles in performance tests | ⚪ Optional; tests only (unless `NO_P99` / `--no-p99`) |
| [**shwild**](https://github.com/synesissoftware/shwild) | Enhanced pattern-match assertions in **xTests** | ⚪ Optional; tests only (unless `NO_SHWILD` / `--no-shwild`) |

When supplying `'--no-cpp'` to **prepare_cmake.sh** — sets the CMake option `NO_TORRENTEOL_CPP_API=ON` — the C++ performance tests are omitted. The **C** unit-tests and component tests still require **STLSoft** and **xTests**.

When supplying `'--no-p99'` — sets `NO_P99=ON` — **p99** is not recognised; performance tests still build but omit percentile columns.

When supplying `'--no-shwild'` — sets `NO_SHWILD=ON` — **shwild** is not recognised and pattern-match assertions are compiled out; other tests still run.


### Related projects

* [**cstring**](https://github.com/synesissoftware/cstring) — exemplar for this tree's layout, tests, and performance harness


### License

**TorrentEOL** is released under the 3-clause BSD license. See [LICENSE](./LICENSE) for details.


<!-- ########################### end of file ########################### -->
