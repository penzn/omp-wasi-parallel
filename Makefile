OPT=-O3
CC=$(WASI_SDK_PATH)/bin/clang --sysroot=$(WASI_SDK_PATH)/share/wasi-sysroot
CFLAGS=$(OPT)
LFLAGS=-Wl,--export-table

OUTS=omp-hello.wasm

all: $(OUTS)

omp-hello.wasm: omp-hello.o kmpc-shim.o
	$(CC) -fopenmp $(CFLAGS) $(LFLAGS) $^ -o $@

kmpc-shim.o: kmpc-shim.c Makefile
	$(CC) -c $(CFLAGS) $< -o $@

omp-hello.o: omp-hello.c Makefile
	$(CC) -fopenmp -c $(CFLAGS) $< -o $@

clean:
	$(RM) *.o *.wasm
