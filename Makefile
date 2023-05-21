
SDL2CFLAGS=$(shell pkg-config sdl2 --cflags)
SDL2LDFLAGS=$(shell pkg-config sdl2 --libs)

CFLAGS=-O3 -Wall -Wextra -Wstrict-prototypes ${SDL2CFLAGS}


all:	browzer-tanx.wasm browzer-tanx

browzer-tanx.wasm:	browzer-tanx.c Makefile
	emcc -DBTWASM=1 -o browzer-tanx.html browzer-tanx.c -s USE_SDL=2
	@echo 'To runbrowzer-tanx.html, run "python3 -m http.server", then browse to localhost:8000/browzer-tanx.html'

browzer-tanx:	browzer-tanx.c Makefile
	gcc ${CFLAGS} -o browzer-tanx browzer-tanx.c ${SDL2LDFLAGS}

clean:
	rm -f browzer-tanx browzer-tanx.html browzer-tanx.js browzer-tanx.wasm
