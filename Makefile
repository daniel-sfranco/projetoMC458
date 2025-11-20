CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: vetores arvore gerador

vetores: vetores.c
	gcc $(CFLAGS) vetores.c -o vetores $(LDFLAGS)

arvore: arvore.c arvore_utils.c
	gcc $(CFLAGS) arvore.c -o arvore $(LDFLAGS)

gerador: gerador.c
	gcc $(CFLAGS) gerador.c -o gerador $(LDFLAGS)

clean:
	rm -f vetores arvore gerador
