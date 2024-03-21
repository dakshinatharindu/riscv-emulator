TARGETS = core
HEADERS = Core.h
SOURCES = main.cpp Core.cpp
DEPENDENCIES = $(SOURCES) $(HEADERS) Makefile

CC = g++

all: $(TARGETS)

$(TARGETS): $(DEPENDENCIES)
	$(CC) -g -o $(TARGETS) $(SOURCES)

test: $(TARGETS)
	./$(TARGETS)

clean:
	rm -f $(TARGETS)
