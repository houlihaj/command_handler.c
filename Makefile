all: command_handler.c
	gcc -std=c99 -o command_handler command_handler.c

clean:
	rm -f command_handler
