OpenMP compilations for Wasm offload
====================================

Examples of single file OpenMP 'offload' to WebAssembly.

- This requires a [change][c] to Clang to define Wasm as a valid offload target
  and also disable multi-stage compilations normally used for native host
  targets
- Import OpenMP API into the module, wasi-parallel Wasm API does not define
  device offload functionality

Examples are:

- [copy.c](copy.c) - copy one array into the other on the device
- [dot.c](dot.c) - dot product
- [matmul.c](matmul.c) - matrix multiplication
- [saxpy.c](saxpy.c) - single-precision `A * X + Y`

To compile, first build modified Clang (apply [patch][c]), then run `make` with
Clang on the path.

[c]: https://github.com/penzn/llvm-project/commit/320765aebcaf86d2f949346ba3b96c565a726893

