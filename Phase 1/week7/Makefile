CFLAGS = -Wall -Wextra -Wstrict-prototypes -g -fsanitize=address,undefined

all: main tests

main: main.c
	clang $(CFLAGS) -o main main.c

tests: tests.c main.c
	clang $(CFLAGS) -o tests tests.c

check: tests
	./tests

clean:
	rm -f main tests
	rm -rf main.dSYM tests.dSYM

.PHONY: all check clean
