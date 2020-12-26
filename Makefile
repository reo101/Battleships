RM = rm -f # for cleaning

CXX = clang++ # g++
CXXFLAGS = -std=c++11 -Wall # -std=c++0x -Wall
CXXDEBUGFLAGS = -fsanitize=address # for tracing back 

OBJECTS = main.cpp

$(OBJECTS): ./include/

all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@.out

debug: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(CXXDEBUGFLAGS) $^ -o $@.out

clean:
	$(RM) *.out

love:
	@echo "not war"
