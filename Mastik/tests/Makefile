FILES= \
       l1irattle.c  \
       l1rattle.c \
       testfr.c \
       testl1.c \
       testl1i.c \
       testl3.c \
       testl1aes.c

prefix=/usr/local
exec_prefix=${prefix}

FTARGETS=$(FILES:.c=)
FOBJS=${FILES:.c=.o}
CFLAGS=-g -O2   -I..
LDFLAGS=-L../src/ -g
LDLIBS=-lmastik -ldwarf -lelf -lbfd 

TARGETS=${FTARGETS} testl1aes
OBJS=${FOBJS} testl1aes.o aes_core.o

all: ${TARGETS}

${TARGETS}: %: %.o 
	${CC} ${LDFLAGS} -o $@ $@.o ${LDLIBS}

testl1aes: testl1aes.o aes_core.o
	${CC} ${LDFLAGS} -o $@ testl1aes.o aes_core.o ${LDLIBS}
       
testl2aes: testl2aes.o aes_core.o
	${CC} ${LDFLAGS} -o $@ $^ ${LDLIBS}

install:


clean:
	rm -f ${TARGETS} ${OBJS} *.sig out

distclean: clean
	rm Makefile
