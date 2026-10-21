# Every .cpp under tests/ is picked up automatically; contributors never need to edit this file.
#
#   make test             build and run all tests
#   make test ONLY=Stack  run only tests whose name contains "Stack"
#   make test SANITIZE=1  also check for memory errors and leaks (what CI runs; Linux/WSL)
#   make clean

CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -g
CPPFLAGS += -Iinclude -Itests -MMD -MP

ifeq ($(WERROR),1)
CXXFLAGS += -Werror
endif
ifeq ($(SANITIZE),1)
CXXFLAGS += -fsanitize=address,undefined -fno-omit-frame-pointer
LDFLAGS  += -fsanitize=address,undefined
endif

BUILD := build
SRCS  := $(shell find tests -name '*.cpp')
OBJS  := $(SRCS:%.cpp=$(BUILD)/%.o)
BIN   := $(BUILD)/run_tests

.PHONY: all test clean

all: $(BIN)

test: $(BIN)
	./$(BIN) $(ONLY)

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

$(BUILD)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD)

-include $(OBJS:.o=.d)
