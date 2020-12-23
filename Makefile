CXX = clang++ # g++
CXXFLAGS = -std=c++11 -Wall # -std=c++0x -Wall

OBJECTS = main.cpp # files

main: $(OBJECTS)
		$(CXX) $(CXXFLAGS) -o $@.out $^

$(OBJECTS): ./include/
