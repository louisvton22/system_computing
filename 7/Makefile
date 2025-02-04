# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -O2 -std=c++17

# Find all .cpp files in the current directory
SRCS = $(wildcard *.cpp)

# Convert .cpp filenames to .o object files (fixing case issue)
OBJS = $(SRCS:.cpp=.o)

# Output executable name
TARGET = main

# Default target: build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile each .cpp file to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove generated files (fixing tab issue)
clean:
		rm -f $(OBJS) $(TARGET)

# Ensure clean is always rebuilt when called
.PHONY: clean
