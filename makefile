CC      = gcc
DEPS_PATH  = include
SRC_PATH = src

ROOT_SRC = main.c
DEPS = pvv.h tools.h graph.h
SRCS_DEPS= pvv.c tools.c graph.c

SRCS_PREFIX = $(ROOT_SRC) $(addprefix $(SRC_PATH)/,$(SRCS_DEPS))
DEPS_PREFIX = $(addprefix $(DEPS_PATH)/,$(DEPS))
OBJS = $(SRCS_PREFIX:.c=.o)

OS_WINDOWS := $(filter Windows_NT,$(OS))

EXE_EXT :=
RM = rm -f
CLEAR_CMD = clear
VALGRIND_SUPPORTED = 1

ifeq ($(OS_WINDOWS),Windows_NT)
	EXE_EXT := .exe
	RM = del /f /q
	CLEAR_CMD = cmd /C cls
	SANITIZERS ?=
	VALGRIND_SUPPORTED = 0
else
	SANITIZERS ?= -fsanitize=address,undefined
endif

CFLAGS_BASE = -Wall -Wextra -std=c99 -I$(DEPS_PATH)
CFLAGS  = $(CFLAGS_BASE) $(SANITIZERS)
LDFLAGS = $(SANITIZERS)

BIN = build$(EXE_EXT)

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes
VALGRIND = valgrind $(VALGRIND_FLAGS)

VALGRIND_FREE_FLAGS = --leak-check=full --show-leak-kinds=definite
VALGRIND_FREE = valgrind $(VALGRIND_FREE_FLAGS)

.PHONY: all build run leaks clean debug

all: build

build: $(BIN)

debug: CFLAGS += -Werror #-DDEBUG -UDEBUG
debug: build run

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c $(DEPS_PREFIX)
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(BIN)
	@$(CLEAR_CMD) 2>/dev/null || true; ./$(BIN) || { stty sane >/dev/null 2>&1 || true; tput cnorm >/dev/null 2>&1 || true; false; }

ifeq ($(VALGRIND_SUPPORTED),1)
leaks:
	@$(MAKE) clean
	@$(MAKE) SANITIZERS= LDFLAGS= $(BIN)
	$(VALGRIND_FREE) ./$(BIN)
else
leaks:
	@echo "Valgrind no está disponible en Windows; ejecuta este objetivo en un entorno Unix-like."
endif

clean:
	-$(RM) $(BIN) $(OBJS)
