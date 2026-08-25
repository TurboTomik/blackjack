NAME := blackjack
SRC_DIR := ./src
BUILD_DIR := ./build
INCLUDE_DIR := ./include
TESTS_DIR := ./tests
BIN_DIR := ./bin

TARGET := $(BIN_DIR)/$(NAME)
TEST_TARGET := $(TESTS_DIR)/run_tests

SRC := $(wildcard $(SRC_DIR)/*.c)
HEADERS := $(wildcard $(INCLUDE_DIR)/*.h)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS := $(OBJ:.o=.d)

LOGIC_SOURCES := $(SRC_DIR)/card.c \
                 $(SRC_DIR)/deck.c \
                 $(SRC_DIR)/hand.c \
                 $(SRC_DIR)/bet.c \
                 $(SRC_DIR)/result.c
TEST_SOURCES := $(wildcard $(TESTS_DIR)/*.c)

CC = gcc
FORMATTER := clang-format
LINTER := clang-tidy
CFLAGS = -Wall -Wextra -Werror -std=c17
CPPFLAGS = -I$(INCLUDE_DIR) -MMD -MP
LDFLAGS = -lncurses

DEBUG_FLAGS := -g -O0
RELEASE_FLAGS := -O2
BUILD ?= debug

ifeq ($(BUILD),release)
    CFLAGS += $(RELEASE_FLAGS)
else
    CFLAGS += $(DEBUG_FLAGS)
endif

.PHONY: all clean test format format-check lint lint-src lint-tests

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SOURCES) $(LOGIC_SOURCES)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^

format:
	@$(FORMATTER) -i $(SRC) $(HEADERS) $(TEST_SOURCES)

format-check:
	@$(FORMATTER) --dry-run -Werror $(SRC) $(HEADERS) $(TEST_SOURCES)

lint: lint-src lint-tests

lint-src:
	@$(LINTER) $(SRC) $(HEADERS) -- $(CFLAGS) -I$(INCLUDE_DIR)

lint-tests:
	@$(LINTER) $(TEST_SOURCES) \
		-checks='-readability-magic-numbers'

lint-fix:
	@$(LINTER) --fix $(SRC) $(INCLUDE_DIR)/* $(TEST_SOURCES) -- $(CFLAGS) -I$(INCLUDE_DIR)

bear:
	@bear -- make clean all

clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR) $(TEST_TARGET)
