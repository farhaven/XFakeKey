xfk: xfk.c keytable.h
	gcc -g -o xfk xfk.c -lX11 -lXtst

test: xfk
	./xfk

clean:
	rm -f xfk keytable.h

debug: xfk
	gdb ./xfk

strip: xfk
	strip xfk

all: strip

table: keytable.h

keytable.h:
	awk -f genktable.awk -- /usr/include/X11/keysymdef.h /usr/include/X11/XF86keysym.h > keytable.h
