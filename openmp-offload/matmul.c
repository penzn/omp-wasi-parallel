// X = Y * Z (inputs are in opposite row-column order)
void matmul(float *X, float *Y, float *Z, unsigned N) {
#pragma omp target teams distribute parallel for collapse(2)
  for (unsigned i = 0; i < N; ++i)
    for (unsigned j = 0; j < N; ++j)
      X[i] = Y[j] * Z[j];
}

int main() {
  const unsigned N = 1024;
  float X[N], Y[N], Z[N];
#pragma omp target data map(from:X[0 : N]) map(to:Y[0 : N]) map(to:Z[0 : N])
  matmul(X, Y, Z, N);
}
