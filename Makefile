OPT=-O3
CC=clang
CFLAGS=$(OPT) --target=wasm32
LFLAGS= -fvisibility=hidden -Wl,--import-memory,--no-entry,--strip-all,--export-dynamic -nostdlib

OUTS=sequential.wasm omp-parallel.wasm omp-parallel-target.wasm

all: $(OUTS)

sequential.wasm: omp-loop.c Makefile
	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@

omp-parallel.wasm: omp-parallel.o kmpc-shim.o
	$(CC) -fopenmp $(CFLAGS) $(LFLAGS) $^ -o $@

omp-parallel-target.wasm: omp-parallel-target.o kmpc-shim.o
	$(CC) -fopenmp $(CFLAGS) $(LFLAGS) $^ -o $@

kmpc-shim.o: kmpc-shim.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

omp-parallel.o: omp-loop.c Makefile
	$(CC) -fopenmp -c $(CFLAGS) $< -o $@

omp-parallel-target.o: omp-loop.c Makefile
	$(CC) -fopenmp -D_TARGET -c $(CFLAGS) $< -o $@

clean:
	rm -f *.wasm
