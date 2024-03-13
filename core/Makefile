TARGET = core
HEADERS = Core.h
SOURCES = main.cpp Core.cpp
DEPENDENCIES = $(SOURCES) $(HEADERS) Makefile

CC = g++

all: $(TARGET)

$(TARGET): $(DEPENDENCIES)
	$(CC) -o $(TARGET) $(SOURCES)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
