# Опции для демона

BUILD = build
CC = gcc
DEBUGGER = gdb
DEBUG_LEVEL = 3
LIB = -lssl -lcrypto
SOURCE = src/daemon
BUILD_DIR = build/daemon
TARGET = reader

# опции для теста
TCC = mpicc
TSOURCE = src/test
TBUILD_DIR = build/test
TTARGET = mpitest
TSRC_SCRIPT = src/script/test.php
TEXEC = mpiexec

#! Количество процессов:
TEST_INSTANCES = 150

# сборка демона без отладочной информации
build: clean
	mkdir -p $(BUILD_DIR)
	$(CC) $(SOURCE)/main.c -o $(BUILD_DIR)/$(TARGET) $(LIB)
# очищает директорию
clean: 
	rm -rf $(BUILD)
# сборка демона с отладочной информацией
debug: clean
	mkdir -p $(BUILD_DIR)
	$(CC) -g$(DEBUG_LEVEL) $(SOURCE)/main.c \
		 -o $(BUILD_DIR)/$(TARGET) $(LIB)
# отладка запуска демона
debug_start: debug
	sudo $(DEBUGGER) --args $(BUILD_DIR)/$(TARGET) --start
# отладка демона
debug_start_fork: debug
	sudo $(DEBUGGER)  --command=.gdb.config \
		--args $(BUILD_DIR)/$(TARGET) --start
# отладка остановки демона
debug_stop: debug
	sudo $(DEBUGGER) --args $(BUILD_DIR)/$(TARGET) --stop
# сборка теста
build_test: 
	mkdir $(TBUILD_DIR)
	cp $(TSRC_SCRIPT) $(TBUILD_DIR)
	$(TCC) $(TSOURCE)/test.c -o $(TBUILD_DIR)/$(TTARGET)
# сборка и тестирование
test: build build_test
	sudo ./$(BUILD_DIR)/$(TARGET) --stop
	sudo ./$(BUILD_DIR)/$(TARGET) --start
	sudo $(TEXEC) -l -n $(TEST_INSTANCES) $(TBUILD_DIR)/$(TTARGET)