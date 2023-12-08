CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic
LDFLAGS = -lstdc++fs

SRCDIR = src
OBJDIR = obj
BINDIR = bin
TESTDIR = test

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
TEST_SOURCES := $(wildcard $(TESTDIR)/*.cpp)
TEST_OBJECTS := $(patsubst $(TESTDIR)/%.cpp, $(OBJDIR)/%.o, $(TEST_SOURCES))
TEST_BINARIES := $(patsubst $(TESTDIR)/%.cpp, $(BINDIR)/%, $(TEST_SOURCES))

MAIN_BINARY = $(BINDIR)/main

.PHONY: all clean test

all: $(MAIN_BINARY)

$(MAIN_BINARY): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_BINARIES)
	@for test_binary in $(TEST_BINARIES); do \
		$$test_binary; \
	done

$(BINDIR)/%: $(OBJDIR)/%.o $(filter-out $(OBJDIR)/main.o, $(OBJECTS))
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)