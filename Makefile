CC = gcc
CFLAGS = 
DEPS = flatner/flatner.c

all: e.o
	./e.o -i input.txt -o output.txt

e.o: lex.yy.c y.tab.c $(DEPS)
	$(CC) $(CFLAGS) lex.yy.c y.tab.c $(DEPS) -lfl -o e.o

lex.yy.c: l.l
	flex l.l

y.tab.c: y.y
	bison -d y.y -Wcounterexamples

clean:
	rm -rf lex.yy.c *.o *.tab.* *.tmp
