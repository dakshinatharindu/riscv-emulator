TARGETS = core
HEADERS = core.h
SOURCES = core.c
DEPENDENCIES = $(SOURCES) $(HEADERS) Makefile

CC = gcc

all: $(TARGETS)

$(TARGETS): $(DEPENDENCIES)
	$(CC) -g -o $(TARGETS) $(SOURCES)

test: $(TARGETS)
	./$(TARGETS)

clean:
	rm -f $(TARGETS)
