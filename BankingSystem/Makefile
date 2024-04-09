# Makefile for Banking System

# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -std=c++11

# Source files
SOURCES = main.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
EXECUTABLE = banking_system

# Build target
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

# Compile source files to object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
