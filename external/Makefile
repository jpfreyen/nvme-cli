CFLAGS += -std=gnu99 -O2 -g -Wall -Werror -fpic
CPPFLAGS += -I../

libfoo.so: foo.h foo.c
	gcc $(CPPFLAGS) ${CFLAGS} -c foo.c
	gcc -o libfoo.so -shared foo.o

clean:
	rm -f *.so *.o
