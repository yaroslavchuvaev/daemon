CC = gcc
BUILD_DIR = build
TARGET = reader
DEBUG = g3

debug:
	mkdir -p $(BUILD_DIR)
	$(CC) -$(DEBUG) main.c -o $(BUILD_DIR)/$(TARGET) -lpthread

build:
	mkdir -p $(BUILD_DIR)
	$(CC) main.c -o $(BUILD_DIR)/$(TARGET) -lpthread

clean:
	rm -r $(BUILD_DIR)
