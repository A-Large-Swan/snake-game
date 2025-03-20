
CC = gcc
CFLAGS = -Wall -Wextra -MMD -MP
LDFLAGS = -lncursesw

TARGET = snake
SRC = snake.c game.c level.c ui.c main.c
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

# Debug build flags
DEBUGFLAGS = -g -DDEBUG
# Release build flags
RELEASEFLAGS = -O2 -DNDEBUG

.PHONY: all clean debug release

all: release

debug: CFLAGS += $(DEBUGFLAGS)
debug: $(TARGET)

release: CFLAGS += $(RELEASEFLAGS)
release: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ) $(DEP)

-include $(DEP)