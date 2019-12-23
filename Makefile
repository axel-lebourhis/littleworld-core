CXX      := g++
CXXFLAGS := -Werror -Wall -O2 -std=c++14
LDFLAGS  := -lsfml-graphics -lsfml-window -lsfml-system
BUILD    := ./build
SRC_DIR  := ./src
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/bin
TARGET   := littleworld
INCLUDE  := -Iinclude/
SRC      :=                      \
	$(wildcard  $(SRC_DIR)/*.cpp)         \

OBJECTS := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(OBJECTS) -o $(APP_DIR)/$(TARGET) $(LDFLAGS)
	@ln -sf $(APP_DIR)/$(TARGET) ./$(TARGET)

.PHONY: all build clean debug release

print-%  : ; @echo $* = $($*)

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
	-@rm -vf ./$(TARGET)
