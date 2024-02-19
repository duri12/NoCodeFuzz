CC=gcc-7
CFLAGS=-I.


poc_v1: 
	gcc -O0 opcode_test.c pht_PP_api.c util.c pht_PP_api.h util.h randomize_pht.o -o phtTest -static

all: poc_v1
v1: poc_v1

clean:
	rm poc_v1
