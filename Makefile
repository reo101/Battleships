RM = rm -f
MKDIR = mkdir -p
ZIP = zip -r

CXX = g++
LD = g++
CXXFLAGS = -std=c++11 -Wall
CXXDEBUGFLAGS = -fsanitize=address
PROG_NAME = battleships

SRC_DIR = ./src
LIB_DIR = ./lib
RES_DIR = ./res
SRC_BUILD_DIR = ./build/src
LIB_BUILD_DIR = ./build/lib
BIN_DIR = ./bin
MAKEFILE_PATH = Makefile
README_PATH = README.md
ARCHIVE_PATH = UP_20-21_fn62555_KP05-prakt.zip

LIB_LIST = $(wildcard $(LIB_DIR)/*.cpp)
LIB_HDR_LIST = $(wildcard $(LIB_DIR)/*.hpp)

SRC_LIST = $(wildcard $(SRC_DIR)/*.cpp)

LIB_OBJ_LIST = $(addprefix $(LIB_BUILD_DIR)/, $(notdir $(LIB_LIST:.cpp=.o)))
SRC_OBJ_LIST = $(addprefix $(SRC_BUILD_DIR)/, $(notdir $(SRC_LIST:.cpp=.o)))
OBJ_LIST = $(LIB_OBJ_LIST) $(SRC_OBJ_LIST)

all: $(PROG_NAME)

archive: $(ARCHIVE_PATH)

$(ARCHIVE_PATH):
	$(ZIP) $@ $(SRC_DIR) $(LIB_DIR) $(RES_DIR) $(MAKEFILE_PATH) $(README_PATH)

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
	$(RM) $(BIN_DIR)/$(PROG_NAME).out $(LIB_BUILD_DIR)/*.o $(SRC_BUILD_DIR)/*.o $(ARCHIVE_PATH)

love:
	@echo "not war"

.PHONY: all archive target compile clean love
