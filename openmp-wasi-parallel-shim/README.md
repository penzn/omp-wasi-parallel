OpenMP POC for wasi-parallel
============================

Wasm compilation for a sample OpenMP program using [wasi-parallel][wp]. Has
only been tested on Linux.

[wp]: https://github.com/WebAssembly/wasi-parallel

## Prerequisites

- [WASI-SDK](https://github.com/WebAssembly/wasi-sdk)
- Make
- [wasmtime with `wasi-parallel` support][aw], more on that below

[aw]: https://github.com/abrown/wasmtime/tree/wasi-parallel

## Building

Install WASI-SDK and set relevant environment variables, in particular
`WASI_SDK_PATH`. Makefile would use it to pick up the compiler and runtime
libraries. Alternatively, pass `WASI_SDK_PATH` to Make directly.

In the default case:

```
$ make
```

### Building wasmtime with wasi-parallel support

Get the code at https://github.com/abrown/wasmtime/tree/wasi-parallel

Install WASI-SDK, set recommended environment variables and also add its `bin`
directory to the `PATH`.

Add `--features wasi-parallel` to `cargo build`.

## Running

Enable `experimental-wasi-parallel` module in `wasmtime`.

The example takes a command-line parameters indicating number of threads to
execute. Passing zero would make it completely sequential, non-integer values
would be treated as zero. For example, to run using four threads:

```
wasmtime --wasi-modules experimental-wasi-parallel omp-hello.wasm 4
```
