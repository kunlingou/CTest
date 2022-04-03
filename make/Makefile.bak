GCC=gcc
CFLAGS := -g -Wall -Wextra
OBJECTS=sort_bubble.o test.o

main: ${OBJECTS}
	${GCC} ${OBJECTS} -o test
	rm -f *.o

clean:
	rm -f *.o test
