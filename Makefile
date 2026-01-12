CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I./src
LDFLAGS = -lncurses

SRCDIR = src
BUILDDIR = build
TARGET = chinese-calendar

# Find all source files recursively
SOURCES = $(shell find $(SRCDIR) -name "*.c")
# Convert src/path/file.c to build/path/file.o
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

TEST_SOURCES = $(wildcard tests/*.c)
TEST_BINS = $(patsubst tests/%.c,$(BUILDDIR)/test_%,$(TEST_SOURCES))

all: $(BUILDDIR) $(TARGET)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)/ui/layout $(BUILDDIR)/ui/components $(BUILDDIR)/ui/visual $(BUILDDIR)/calendar $(BUILDDIR)/almanac $(BUILDDIR)/interaction $(BUILDDIR)/ncurses $(BUILDDIR)/utils

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_BINS)
	@echo "Running all tests..."
	@for test in $(TEST_BINS); do \
		echo ""; \
		echo "Running $$test..."; \
		$$test || exit 1; \
	done
	@echo ""
	@echo "All tests passed!"

$(BUILDDIR)/test_%: $(filter-out build/main.o,$(OBJECTS)) tests/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(filter-out build/main.o,$(OBJECTS)) tests/$*.c -o $@ $(LDFLAGS)

clean:
	rm -rf $(BUILDDIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run test
