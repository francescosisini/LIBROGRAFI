HEADERS = lib/include/libagri.h

default: libagri.o

libagri.o: lib/src/libagri.c $(HEADERS)
	gcc -c lib/src/libagri.c -o lib/libagri.o -Ilib/include

clean:
	-rm -f lib/libagri.o
