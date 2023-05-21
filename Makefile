
all:	browzer-tanx.wasm browzer-tanx

browzer-tanx.wasm:	browzer-tanx.c Makefile
	emcc -o browzer-tanx.html browzer-tanx.c
	@echo 'To run browzer-tanx.html, run "python3 -m http.server", then browse to localhost:8000/browzer-tanx.html'

browzer-tanx:	browzer-tanx.c Makefile
	gcc -O3 -Wall -Wextra -Wstrict-prototypes -o browzer-tanx browzer-tanx.c

clean:
	rm -f browzer-tanx browzer-tanx.html browzer-tanx.js browzer-tanx.wasm
