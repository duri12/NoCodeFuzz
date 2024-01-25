SRCS=${wildcard src/*.py}
ICONS=${wildcard data/icons/*.png}

prefix=/usr/local
exec_prefix=${prefix}
datarootdir=${prefix}/share
datadir=${datarootdir}

mastiktoolsdir=${datadir}/mastik/tools
doubloonsrcdir=${mastiktoolsdir}/doubloon

edit = sed \
       -e 's|@DOUBLOON_TEXTBOX_HEIGHT[@]|30|g' \
       -e 's|@DOUBLOON_HAVE_DWARF[@]|True|g' \
       -e 's|@DOUBLOON_EXPERIMENTAL[@]|False|g' \
       -e 's|@DOUBLOON_INSTALL_DATADIR[@]|${doubloonsrcdir}/data|g'


all: doubloon src/config.py


install: all
	install -d ${doubloonsrcdir}
	install ${SRCS} ${doubloonsrcdir}
	install src/config.py ${doubloonsrcdir}
	cp -r data ${doubloonsrcdir}
	install -d ${exec_prefix}/bin
	install doubloon ${exec_prefix}/bin

doubloon:
	echo "#!/bin/bash" > doubloon
	echo "/usr/bin/python3 ${doubloonsrcdir}" >> doubloon
	chmod +x doubloon

src/config.py: src/config.py.in
	rm -f src/config.py
	${edit} src/config.py.in > src/config.py

clean: 
	rm -f doubloon src/config.py


distclean: clean
	rm Makefile
