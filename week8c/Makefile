CC     = clang
CFLAGS = -Wall -Wextra -g -Wstrict-prototypes
SRCS   = src/events_main.c src/events.c
HDRS   = src/events.h

main: $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o main $(SRCS)

clean:
	rm -f main

.PHONY: clean
