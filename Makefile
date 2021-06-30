CC=clang
CFLAGS=-O3 --target=wasm32 -fvisibility=hidden
LFLAGS=-Wl,--import-memory,--no-entry,--strip-all,--export-dynamic,--allow-undefined-file=kmpc.syms -nostdlib

OUTS=sequential.wasm omp-parallel.wasm omp-parallel-target.wasm

all: $(OUTS)

sequential.wasm: omp-loop.c Makefile
	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@

omp-parallel.wasm: omp-loop.c Makefile
	$(CC) -fopenmp $(CFLAGS) $(LFLAGS) $< -o $@

omp-parallel-target.wasm: omp-loop.c Makefile
	$(CC) -fopenmp -D_TARGET $(CFLAGS) $(LFLAGS) $< -o $@

clean:
	rm -f *.wasm