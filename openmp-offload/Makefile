CC=clang
CFLAGS=-O3 --target=wasm32 -fopenmp -fopenmp-targets=wasm32
LFLAGS=-Wl,--no-entry,--allow-undefined-file=kmpc.syms -nostdlib

TARGETS=copy.wasm saxpy.wasm dot.wasm matmul.wasm

all: $(TARGETS)

%.wasm: %.c
	$(CC) $(CFLAGS) $(LFLAGS) $^ -o $@

clean:
	$(RM) $(TARGETS)
