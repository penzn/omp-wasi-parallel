float dot(float *X, float *Y, unsigned N) {
  float res = 0.0;
#pragma omp target teams distribute parallel for
  for (unsigned i = 0; i < N; ++i)
    res = X[i] * Y[i];
  return res;
}

int main() {
  const unsigned N = 1024;
  float X[N], Y[N];
#pragma omp target data map(to:X[0 : N]) map(to:Y[0 : N])
  dot(X, Y, N);
}
