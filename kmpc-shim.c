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

WASI_PARALLEL_IMPORT("parallel_for")
extern int parallel_for(
    wasi_worker worker_func,
    int num_threads, int block_size,
    const void * in_buffers_start, int in_buffers_len,
    const void * out_buffers_start, int out_buffers_len);


void wasi_unwrapper(int thread_id, int num_threads, int block_size,
  void (*omp_worker)(int*, int*, ...), int ignore /* == 1*/, ... /* FIXME */) {
}

#ifndef va_list
typedef __builtin_va_list va_list;
#endif
#ifndef va_start
#define va_start(a, l) __builtin_va_start((a), (l))
#endif

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

  // Set up a buffer with function pointer and number of parameters

  // Set up a buffer with all worker arguments

  // Input buffers: function pointer and arguments
  // Output buffers: arguments

  // Call wasi's parallel for function with a wrapper
  parallel_for(wasi_unwrapper, num_threads, 1 /* block_size */, 0, 0, 0, 0);
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
