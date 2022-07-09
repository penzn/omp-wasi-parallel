void saxpy(float *X, float *Y, float D, unsigned N) {
#pragma omp target teams distribute parallel for
  for (unsigned i = 0; i < N; ++i)
    Y[i] = D * X[i] + Y[i];
}

int main() {
  const unsigned N = 1024;
  float X[N], Y[N], D;
#pragma omp target data map(to:X[0 : N]) map(tofrom:Y[0 : N])
  saxpy(X, Y, D, N);
}
