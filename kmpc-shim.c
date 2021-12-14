// TODO
typedef struct { int a; int b; int c; int d; char* e; } ident_t;

void __kmpc_for_static_fini(ident_t * ptr, int todo) {
  // TODO
}

void __kmpc_fork_call(ident_t * ptr, int num_args, void (*worker)(int*, int*, ...), ...) {
  // TODO
}

void __kmpc_for_static_init_4u(ident_t * ptr, int need, int to, int* figure, int* it, int* out, int* at, int some, int point) {
  // TODO
}

int __kmpc_global_thread_num(ident_t * ptr) {
  return 0; // TODO
}

void __kmpc_push_num_threads(ident_t * ptr, int gtid, int num_threads) {
  // TODO save thread number
}
