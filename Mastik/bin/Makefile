FILES= \
       FR-trace.c

TARGETS=$(FILES:.c=)
OBJS=${FILES:.c=.o}
CFLAGS=-g -O2   -I..
LDFLAGS=-L../src/ -g
LDLIBS=-lmastik -ldwarf -lelf -lbfd 

prefix=/usr/local
exec_prefix=${prefix}

all: ${TARGETS}

install: ${TARGETS}
	install -d ${exec_prefix}/bin
	install ${TARGETS} ${exec_prefix}/bin

${TARGETS}: %: %.o 
	${CC} ${LDFLAGS} -o $@ $@.o ${LDLIBS}


clean:
	rm -f ${TARGETS} ${OBJS} *.sig out

distclean: clean
	rm Makefile
