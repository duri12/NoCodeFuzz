LIB=libmastik.a
LIBSRCS= \
	cb.c \
	ff.c \
	fr.c \
	l1.c \
	l1i.c \
	l2.c \
	l3.c \
	lx.c \
	mm.c \
	pda.c \
	util.c \
	symbol.c \
	synctrace.c \
	timestats.c \
	vlist.c \
	symbol_bfd.c

prefix=/usr/local
exec_prefix=${prefix}

LIBOBJS=${LIBSRCS:.c=.o}
VERSION=$(shell cut -f 1 -d \  ../VERSION)

all: ${LIB} ${TARGETS}


include LocalMakefile
CFLAGS=-g -O2   -I.. -DNDEBUG ${EXTRA_CFLAGS} 

${LIB}:${LIBOBJS}
	ar crv ${LIB} ${LIBOBJS}
	ranlib ${LIB}

install: ${LIB}
	install -d ${exec_prefix}/lib
	install ${LIB} ${exec_prefix}/lib

l3.o: ../mastik/l3.h vlist.h timestats.h ../mastik/low.h config.h ../mastik/mm.h mm-impl.h

l2.o: ../mastik/l2.h vlist.h timestats.h ../mastik/low.h config.h ../mastik/mm.h mm-impl.h

mm.o: vlist.h ../mastik/low.h config.h ../mastik/mm.h mm-impl.h

vlist.o: vlist.h config.h

timestats.o: timestats.h config.h


#pp.o: vlist.h pp.h low.h

l1.o: ../mastik/l1.h ../mastik/low.h  config.h ../mastik/mm.h mm-impl.h

l1i.o: ../mastik/l1i.h ../mastik/low.h config.h

ff.o: ../mastik/ff.h ../mastik/low.h vlist.h timestats.h config.h

fr.o: ../mastik/fr.h ../mastik/low.h vlist.h config.h

pda.o: ../mastik/pda.h ../mastik/low.h vlist.h config.h


symbol.o: ../mastik/symbol.h ../mastik/util.h config.h

LocalMakefile:
	touch LocalMakefile

clean:
	rm -f ${LIB} ${LIBOBJS}

distclean: clean
	rm Makefile config.h
