CC = g++
CFLAGS =-Wall -Wextra -std=c++17 -O3 #-g -fsanitize=address -fsanitize=undefined -fsanitize=leak -std=c++17
LDFLAGS =-lraylib -lm
TARGET = main
QUICKJS_DIR = ../quickjs


SOURCES = main.cpp


INCLUDES = -I$(QUICKJS_DIR)


LIBS = -L$(QUICKJS_DIR) -lquickjs

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(SOURCES) $(LIBS) $(LDFLAGS)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
