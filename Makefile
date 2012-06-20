all: clean cva-match

debug: cva-match-debug
	gcc cva-match.o `pkg-config --libs opencv` -o cva-match

cva-match: cva-match.o
	gcc cva-match.o `pkg-config --libs opencv` -o cva-match

cva-match-debug: cva-match-debug.o
	gcc src/cva-match.c -DDEBUG `pkg-config --cflags opencv` -c -o cva-match.o

cva-match.o:
	gcc src/cva-match.c `pkg-config --cflags opencv` -c -o cva-match.o

clean:
	rm *.o cva-match -f
