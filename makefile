CXX := g++
CXXFLAGS := -std=c++11 -Wall -DIL_STD -m64 -fPIC -g3

UNAME_S := $(shell uname -s)

SOURCE_DIR := src/
OBJ_DIR := obj/

ifeq ($(UNAME_S), Linux)
SOURCE_DIR := src
OBJ_DIR := obj
endif

ALL_FILES := $(shell find $(SOURCE_DIR))
DIRS := $(patsubst $(SOURCE_DIR)/%, $(OBJ_DIR)/%, $(shell find $(SOURCE_DIR)/ -type d))
SOURCES := $(filter %.cpp, $(ALL_FILES))
OBJECTS := $(patsubst $(SOURCE_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
HEADERS := $(filter %.h, $(ALL_FILES))

EXECUTABLE = mlp

$(EXECUTABLE): $(OBJECTS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(LIB) $(OBJECTS) -o $(EXECUTABLE)

$(OBJECTS): $(OBJ_DIR)/%.o : $(SOURCE_DIR)/%.cpp | $(DIRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(DIRS):
	mkdir -p $@

.PHONY: clean rebuild
clean:
	$(RM) $(EXECUTABLE) $(OBJECTS)

rebuild:
	make clean
	make