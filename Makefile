CC = gcc
CFLAGS =  -g # -fsanitize=address 
DEPS = flatner/flatner.c flatner/block_info.c flatner/exporter.c flatner/tac.c flatner/instructions_processing.c flatner/expression.c flatner/output.c flatner/utils.c flatner/loopCounter.c flatner/statements.c data-structures/array/array.c data-structures/tree/tree.c data-structures/stack/stack.c data-structures/queue/queue.c 

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
