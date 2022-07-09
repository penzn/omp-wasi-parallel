void copy(float *X, float *Y, unsigned N) {
#pragma omp target teams distribute parallel for
  for (unsigned i = 0; i < N; ++i)
    X[i] = Y[i];
}

int main() {
  const unsigned N = 1024;
  float X[N], Y[N];
#pragma omp target data map(from:X[0 : N]) map(to:Y[0 : N])
  copy(X, Y, N);
}
