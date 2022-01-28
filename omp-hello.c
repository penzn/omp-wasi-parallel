#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
  if (argc != 2) { // Expect one argument
    fprintf(stderr, "Usage: %s <number of threads>, invalid values are ignored\n", argv[0]);
    return 1;
  }
  int num = atoi(argv[1]);

  if (num == 0) { // No multithreading
    printf("Hello world\n");
  }

#pragma omp parallel num_threads(num)
  {
    printf("Hello threaded world\n");
  }
  return 0;
}
