CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lncurses

TARGET = snake
SRC = snake.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)