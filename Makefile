make:
	gcc -o prog main.c lexer.c parser.c
	./prog

clean:
	rm prog

debug:
	gcc -g -o prog main.c lexer.c
	gdb prog