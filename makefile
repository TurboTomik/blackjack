NAME := blackjack
SRC_DIR := ./src
BUILD_DIR := ./build
INCLUDE_DIR := ./include
TESTS_DIR := ./tests
BIN_DIR := ./bin

TARGET := $(BIN_DIR)/$(NAME)

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS := $(OBJ:.o=.d)

CC = gcc
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

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
