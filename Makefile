RM = rm -f
MKDIR = mkdir -p

CXX = g++
LD = g++
CXXFLAGS = -std=c++11 -Wall
CXXDEBUGFLAGS = -fsanitize=address
PROG_NAME = battleships

SRC_DIR = ./src
LIB_DIR = ./lib
SRC_BUILD_DIR = ./build/src
LIB_BUILD_DIR = ./build/lib
BIN_DIR = ./bin

LIB_LIST = $(wildcard $(LIB_DIR)/*.cpp)
LIB_HDR_LIST = $(wildcard $(LIB_DIR)/*.hpp)

SRC_LIST = $(wildcard $(SRC_DIR)/*.cpp)

LIB_OBJ_LIST = $(addprefix $(LIB_BUILD_DIR)/, $(notdir $(LIB_LIST:.cpp=.o)))
SRC_OBJ_LIST = $(addprefix $(SRC_BUILD_DIR)/, $(notdir $(SRC_LIST:.cpp=.o)))
OBJ_LIST = $(LIB_OBJ_LIST) $(SRC_OBJ_LIST)

all: $(PROG_NAME)

target: $(PROG_NAME)

$(PROG_NAME): compile | $(BIN_DIR)
	$(LD) $(OBJ_LIST) -o $(BIN_DIR)/$@.out

$(BIN_DIR):
	$(MKDIR) $(BIN_DIR)

compile: $(LIB_OBJ_LIST) $(SRC_OBJ_LIST)

$(LIB_BUILD_DIR)/%.o: $(LIB_DIR)/%.cpp $(LIB_DIR)/%.hpp | $(LIB_BUILD_DIR)
	$(CXX) -c -o $@ $(CXXFLAGS) $<

$(LIB_BUILD_DIR):
	$(MKDIR) $(LIB_BUILD_DIR)

$(SRC_BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(LIB_HDR_LIST) | $(SRC_BUILD_DIR) 
	$(CXX) -c -o $@ $(CXXFLAGS) $<

$(SRC_BUILD_DIR):
	$(MKDIR) $(SRC_BUILD_DIR)

$(LIB_HDR_LIST):
	$(LIB_DIR)

clean:
	$(RM) $(BIN_DIR)/$(PROG_NAME).out $(LIB_BUILD_DIR)/*.o $(SRC_BUILD_DIR)/*.o

love:
	@echo "not war"

.PHONY: all target compile clean love
