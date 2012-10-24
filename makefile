CC = gcc
DEBUGGER = gdb
BUILD_DIR = build
TARGET = reader
DEBUG_LEVEL = 3
LIB = -lssl -lcrypto

# строит демон без отладочной информации
build: clean
	mkdir -p $(BUILD_DIR)
	$(CC) main.c -o $(BUILD_DIR)/$(TARGET) $(LIB)

# очищает директорию
clean: 
	rm -rf $(BUILD_DIR)

# строит демон с отладочной информацией
debug: clean
	mkdir -p $(BUILD_DIR)
	$(CC) -g$(DEBUG_LEVEL) main.c \
		 -o $(BUILD_DIR)/$(TARGET) $(LIB)

# set follow-fork-mode child
debug_start: debug
	sudo $(DEBUGGER) --args $(BUILD_DIR)/$(TARGET) --start

debug_start_fork: debug
	sudo $(DEBUGGER)  --command=.gdb.config \
		--args $(BUILD_DIR)/$(TARGET) --start

debug_stop: debug
	sudo $(DEBUGGER) --args $(BUILD_DIR)/$(TARGET) --stop