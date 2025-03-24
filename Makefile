CC = gcc
CFLAGS = -Wall -Wextra -MMD -MP -Iinclude
LDFLAGS = -lncursesw

TARGET = snake
SRC_DIR = src
BUILD_DIR = build
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
DEP = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.d,$(SRC))

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

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(TARGET) $(OBJ) $(DEP)

-include $(DEP)