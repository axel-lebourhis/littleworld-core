CXX         := g++
CXXFLAGS    := -Werror -Wall -std=c++14
LDFLAGS     := -lsfml-graphics -lsfml-window -lsfml-system
BUILD       := ./build
SRC_DIR     := ./src
TEST_DIR    := ./test
OBJ_DIR     := $(BUILD)/obj
APP_DIR     := $(BUILD)/bin
TARGET      := littleworld
INCLUDE     := -Iinclude/
LIB_DIR     := $(SRC_DIR)/lib
LIB_OBJ_DIR := $(BUILD)/obj/lib
LIB_SRC     := $(wildcard $(LIB_DIR)/*.cpp)
LIB_OBJ     := $(LIB_SRC:$(LIB_DIR)/%.cpp=$(LIB_OBJ_DIR)/%.o)

ifeq ($(BUILD_TEST),true)
	SRC += $(wildcard  $(TEST_DIR)/*.cpp)
	OBJ := $(SRC:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)
	CXXFLAGS += -DTEST
else
	SRC += $(wildcard  $(SRC_DIR)/*.cpp)
	OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
endif

release: CXXFLAGS += -O2
release: MSG="Building in release mode"
release: printstr-MSG all

debug: CXXFLAGS += -DDEBUG -g
debug: MSG="Building in debug mode"
debug: printstr-MSG all

all: build $(APP_DIR)/$(TARGET)

ifeq ($(BUILD_TEST),true)
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<
else
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<
endif

$(LIB_OBJ_DIR)/%.o: $(LIB_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(LIB_OBJ) $(OBJ)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(OBJ) $(LIB_OBJ) -o $(APP_DIR)/$(TARGET) $(LDFLAGS)
	@ln -sf $(APP_DIR)/$(TARGET) ./$(TARGET)

.PHONY: all build clean debug release

printvar-%  : ; @echo "$* = $($*)"
printstr-%  : ; @echo "$($*)"

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

clean:
	-@rm -rvf $(OBJ_DIR)
	-@rm -vf ./$(TARGET)
