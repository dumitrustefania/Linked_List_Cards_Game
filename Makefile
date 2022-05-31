# Copyright 2022 Dumitru Bianca Stefania - 312CA

CFLAGS=-Wall -Wextra -g -std=c99 

build:
	gcc $(CFLAGS) tema1.c functions.c auxiliary.c linked_list.c -o tema1 

pack:
	zip -FSr 312CA_DumitruBiancaStefania_Tema1.zip README Makefile *.c *.h

clean:
	rm -f tema1

.PHONY: pack clean
