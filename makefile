CC = gcc
<<<<<<< HEAD
DEBUGGER = gdb
BUILD_DIR = build
TARGET = reader
DEBUG_LEVEL = 3


build: clean
	mkdir -p $(BUILD_DIR)
	$(CC) main.c -o $(BUILD_DIR)/$(TARGET)

clean: 
	rm -rf $(BUILD_DIR)

debug: clean
	mkdir -p $(BUILD_DIR)
	$(CC) -g$(DEBUG_LEVEL) main.c -o $(BUILD_DIR)/$(TARGET)

debug_start: debug
	sudo $(DEBUGGER) --args $(BUILD_DIR)/$(TARGET) --start

debug_stop: debug
	sudo $(DEBUGGER) --args $(BUILD_DIR)/$(TARGET) --stop

