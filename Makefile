BUILD_DIR := ./build

$(shell mkdir -p $(BUILD_DIR))

build:
	gcc -o $(BUILD_DIR)/xwc ./xwc.c

.PHONY: build

run: build
	./$(BUILD_DIR)/xwc

.PHONY: run