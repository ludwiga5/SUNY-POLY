CC = gcc
CFLAGS = -Iinclude -w -g
SRC = src/tinycpu.c

# Platform detection
ifeq ($(OS),Windows_NT)
    LIBS = -lgdi32 -lopengl32 -lwinmm
    EXT = .exe
else
    UNAME := $(shell uname -s)
    ifeq ($(UNAME),Darwin)
        LIBS = -framework Cocoa -framework OpenGL -framework IOKit
    else
        LIBS = -lX11 -lGL -lm -ldl -lpthread
    endif
    EXT = 
endif

all: tinyCPU$(EXT)

tinyCPU$(EXT): src/main.c $(SRC)
	$(CC) $^ $(CFLAGS) -o $@ $(LIBS)

test: src/test.c $(SRC)
	$(CC) $^ $(CFLAGS) -o tinyCPU_test$(EXT) $(LIBS)

clean:
	rm -f tinyCPU tinyCPU.exe tinyCPU_test tinyCPU_test.exe

.PHONY: all test clean