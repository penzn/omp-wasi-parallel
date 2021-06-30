OpenMP to WebAssembly compilation demo
======================================

Wasm compilation for a sample OpenMP program, including `omp target`.

## Prerequisites

- Clang
- Make

## The example

At the core it is this function

```C
void foo(float * bar, float * baz, unsigned N) {
  for (unsigned i = 0; i < N; ++i) {
    bar[i] = baz[i] * 2;
  }
}
```

but [parallelized](omp-loop.c) two ways using OpenMP.

## Building 

```
$ make
```

This creates three Wasm binaries: sequential, host-only, and device. The latter
two would contain calls to LLVM OpenMP runtime, which are declared imports.
