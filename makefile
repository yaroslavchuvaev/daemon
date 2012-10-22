CC = gcc
BUILD_DIR = build
TARGET = reader

build:
	mkdir -p $(BUILD_DIR)
	$(CC) main.c -o $(BUILD_DIR)/$(TARGET)

clean:
	rm -r $(BUILD_DIR)
