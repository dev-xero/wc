BUILD_DIR := ./build

$(shell mkdir -p $(BUILD_DIR))

build:
	gcc -o $(BUILD_DIR)/wc ./wc.c

.PHONY: build

run: build
	./$(BUILD_DIR)/wc -c test.txt

.PHONY: run