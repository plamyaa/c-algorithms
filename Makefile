CC = gcc
CFLAGS = -Wall -Wextra -std=c11
BUILD_DIR = build

DIR = $(dir $(BUILD_DIR)/$(basename $(FILE)))

FILES = $(FILE) utils.c

all: compile_and_run

compile_and_run: $(BUILD_DIR)/$(basename $(FILE))
	./$<

$(BUILD_DIR)/$(basename $(FILE)): $(FILES)
	mkdir -p $(DIR)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all compile_and_run clean
