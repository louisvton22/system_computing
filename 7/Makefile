################################################################################
# Cross-Platform Makefile for C++ Projects (Windows & Unix Compatible)
################################################################################

# Detect OS (Windows or Unix)
ifeq ($(OS), Windows_NT)
    RM      = del /Q
    RMDIR   = rmdir /S /Q
    MKDIR   = if not exist $(1) mkdir $(1)
    EXEEXT  = .exe
else
    RM      = rm -f
    RMDIR   = rm -rf
    MKDIR   = mkdir -p
    EXEEXT  =
endif

################################################################################
# Project Configuration
################################################################################

CXX      = g++
CXXFLAGS = -Wall -Wextra -g -std=c++17
TARGET   = main$(EXEEXT)  # The output executable

# Automatically find all .cpp files in the directory
SRCS     = $(wildcard *.cpp)
OBJS     = $(SRCS:.cpp=.o)
EXTENSION = .asm
################################################################################
# Build Rules
################################################################################

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ 

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

clean:
	$(RM) $(OBJS)
	$(RM) $(TARGET)
	$(RM) /S .\*.asm || exit 0
distclean: clean
	# Additional cleanup if needed

.PHONY: all clean distclean
