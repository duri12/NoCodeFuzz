HEADERS= \
	cb.h \
	ff.h \
	fr.h \
	impl.h \
	info.h \
	l1.h \
	l1i.h \
	l2.h \
	l3.h \
	low.h \
	lx.h \
	mm.h \
	pda.h \
	symbol.h \
	synctrace.h \
	transient.h \
	util.h

prefix=/usr/local
exec_prefix=${prefix}

all: ${HEADERS}


install: ${HEADERS}
	install -d ${prefix}/include/mastik
	install ${HEADERS} ${prefix}/include/mastik


clean:

distclean: clean
	rm Makefile
