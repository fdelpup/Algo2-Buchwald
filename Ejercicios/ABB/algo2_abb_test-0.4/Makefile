CFLAGS := -g -std=c99 -Wall -Wformat=2
CFLAGS += -Wshadow -Wpointer-arith -Wunreachable-code
CFLAGS += -Wconversion -Wno-sign-conversion -Wbad-function-cast

# Se puede comentar durante el desarrollo.
CFLAGS += -Werror

test: abb_aux
	./abb_test.py

abb_aux: abb.o abb_aux.o

# Dependencias adicionales.
-include deps.mk

clean:
	rm -f abb_aux *.o

.PHONY: test clean
