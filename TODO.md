# torrenteol - TODO <!-- omit in toc -->


## Table of Contents <!-- omit in toc -->

- [Functional improvements](#functional-improvements)
- [Performance improvements](#performance-improvements)
- [Packaging improvements](#packaging-improvements)


## Functional improvements

* [ ] Read a line into a caller-supplied block, recognising LF, CRLF, and CR as one terminator each;
* [ ] Allocate and return a line, with the same terminator rules;
* [ ] Report which terminator was consumed;
* [ ] Define the contract for a final line that has no terminator;
* [ ] Examples for both storage policies;


## Performance improvements

* [ ] Block scan of a regular file, timed against `fgets` and POSIX `getline`;
* [ ] Publish the comparison table from **test.performance.torrenteol**;


## Packaging improvements

* [ ] GitHub release for 0.1.0-alpha1;
* [ ] vcpkg;
* [ ] Homebrew;


<!-- ########################### end of file ########################### -->
