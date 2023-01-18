CC := gcc
CXX := g++
CFLAGS := -Wall -Wextra -O2g -ggdb3
CXXFLAGS := -Wall -Wextra -Wno-c++17-extensions -O2 -ggdb3 -std=c++20 $(shell sdl2-config --cflags) -Iinclude
LDFLAGS := $(shell sdl2-config --libs) -lSDL2_image

TARGET_EXEC := ietto

BUILD_DIR := build
SRC_DIRS := src

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS := $(INC_FLAGS) -MMD -MP

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	mv $(BUILD_DIR)/$(TARGET_EXEC) .

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -r $(BUILD_DIR)
	rm $(TARGET_EXEC)

-include $(DEPS)
