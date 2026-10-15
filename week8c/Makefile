CC     = clang
CFLAGS = -Wall -Wextra -g -Wstrict-prototypes
SRCS   = src/events_main.c src/events.c
HDRS   = src/events.h

ASAN_FLAGS = -fsanitize=address -fno-omit-frame-pointer

main: $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o main $(SRCS)

asan: $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) -o main_asan $(SRCS)

clean:
	rm -f main main_asan

.PHONY: clean asan