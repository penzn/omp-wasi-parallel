__attribute__ ((visibility("default")))
void foo(float * bar, float * baz, unsigned N) {
#ifdef _TARGET
  #pragma omp target
#endif
  #pragma omp parallel for schedule(static)
  for (unsigned i = 0; i < N; ++i) {
    bar[i] = baz[i] * 2;
  }
}
