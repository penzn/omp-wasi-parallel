#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>

// Real arguments to wasi-parallel worker are, in order:
// - thread id
// - number of threads
// - block size
// - a number of input arrays, each followed by its length
//
// Note: We have to use void* to avoid argument list mismatches.
//typedef void (*wasi_worker)(int thread_id, int num_threads, int block_size, ...);
typedef void * wasi_worker;

#define WASI_PARALLEL_IMPORT(func_name) __attribute__((import_module("wasi_ephemeral_parallel"), import_name(func_name)))

// wasi-parallel device kinds
typedef enum
{
    CPU = 0,
    DISCRETE_GPU,
    INTEGRATED_GPU,
} DeviceKind;

// wasi-parallel buffer access controls
typedef enum
{
    Read = 0,
    Write,
    ReadWrite,
} BufferAccess;

// Devices and buffers
WASI_PARALLEL_IMPORT("get_device") extern int get_device(DeviceKind hint, int* device);
WASI_PARALLEL_IMPORT("create_buffer") extern int create_buffer(int device, int size, BufferAccess access, int* buffer);
WASI_PARALLEL_IMPORT("read_buffer") extern int read_buffer(int buffer, void *data, int size);
WASI_PARALLEL_IMPORT("write_buffer") extern int write_buffer(void *data, int size, int buffer);

// Parallel execution
WASI_PARALLEL_IMPORT("parallel_for")
extern int parallel_for(
    wasi_worker worker_func,
    int num_threads, int block_size,
    const void * in_buffers_start, int in_buffers_len,
    const void * out_buffers_start, int out_buffers_len);

// Call actual OpenMP ouplined function
//
// \param thread_id thread id
// \param num_threads number of threads
// \param block_size block size
//
// The following is for OpenMP worker execution:
//
// \param workers pointer to work function (contents of wasi-parallel buffer)
// \param workers_size how many worker functions (size of wasi-parallel buffer)
// \param inputs pointers to worker function arguments (contents of
//        wasi-parallel buffer)
// \param inputs_size how many worker functions arguments (size of
//        wasi-parallel buffer)
// \param outputs pointers to worker function arguments (contents of
//        wasi-parallel buffer)
// \param outputs_size how many worker functions arguments (size of
//        wasi-parallel buffer)
void wasi_unwrapper(int thread_id, int num_threads, int block_size,
  void ** workers, int workers_size, void ** inputs, int inputs_size,
  void ** outputs, int outputs_size) {

  // TODO wasmtime panics on any calls from the worker

  //Assumptions about the input
  assert(workers_size == 1);
  assert(inputs_size == outputs_size);
  // Inputs and outpus are expected to be the same

  // Call OpenMP worker, beware of Wasm's variadic function emulation
  //
  // OpenMP workers are variadic, which is emulated in WebAssembly using
  // pointer to the variadic part of the argument list. We can explicitly pass
  // the argument array in
  if (inputs_size == 0) {
    ((void (*)(int*, int*))workers[0])(&thread_id, &thread_id);
  else {
    ((void (*)(int*, int*, void**))workers[0])(&thread_id, &thread_id, inputs);
  }
}

// TODO
typedef struct { int a; int b; int c; int d; char* e; } ident_t;

void __kmpc_for_static_fini(ident_t * ptr, int todo) {
  // TODO
}

void __kmpc_fork_call(ident_t * ptr, int num_args, void (*worker)(int*, int*, ...), ...) {
  // TODO
  // The issue with wasi-parallel's parallel_for is that it operates on its own
  // idea of memory buffer, rather than regular function arguments, even for
  // CPU case.

  int num_threads = ptr->a; // FIXME this is not how OpenMP would normally work

  // Collect worker arguments
  void ** args = malloc(sizeof(void*) * num_args); // Free after `parallel_for()`
  va_list vl;
  va_start(vl, worker);
  for (int i = 0; i < num_args; ++i) {
    args[i] = va_arg(vl, void*);
  }
 
  // Setup device
  int device;
  get_device(CPU, &device);

  // Buffer containing the actual worker function
  int worker_handle;
  create_buffer(device, sizeof(void*), Read, &worker_handle);
  write_buffer(&worker, sizeof(void*), worker_handle);

  // Buffer with worker arguments
  int args_handle;
  create_buffer(device, sizeof(void*) * num_args, Read, &args_handle);
  write_buffer(args, sizeof(void*) * num_args, args_handle);

  // Arrays of handles
  int input_buffers[] = {worker_handle, args_handle};
  int output_buffers[] = {args_handle};

  // Call wasi's parallel for function with a wrapper
  parallel_for(wasi_unwrapper, num_threads, 1 /* block_size */,
               input_buffers, sizeof(input_buffers) / sizeof(input_buffers[0]),
               output_buffers, sizeof(output_buffers) / sizeof(output_buffers[0]));

  free(args);
}

void __kmpc_for_static_init_4u(ident_t * ptr, int need, int to, int* figure, int* it, int* out, int* at, int some, int point) {
  // TODO
}

int __kmpc_global_thread_num(ident_t * ptr) {
  return 0; // TODO
}

void __kmpc_push_num_threads(ident_t * ptr, int gtid, int num_threads) {
  // FIXME a hack, this is not how OpenMP runtime works
  ptr->a = num_threads;
}
