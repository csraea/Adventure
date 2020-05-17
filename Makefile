CC = gcc
CFLAGS = -std=c11 -Werror -Wconversion -Wall -g
LDLIBS = -lm
OBJECTS = $(SOURCES:.c=.o)

OUTPUT = game
SOURCES = main.c container.c room.c command.c game.c backpack.c item.c parser.c world.c person.c event.c

.PHONY: all clean cpp

all: $(OUTPUT)

clean:
	rm -rf *.o $(OUTPUT)
cpp:
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT): $(OBJECTS)
	$(CC) $(LDLIBS) $(OBJECTS) -o $@
