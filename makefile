# tool macros
CC ?= gcc
CXX ?= g++
CXXWIN ?= x86_64-w64-mingw32-g++ --static
CFLAGS := -O1 -Wall -Wextra -Wpedantic -Wconversion \
		  -Wcast-align -Wunused -Wold-style-cast \
		  -Wpointer-arith -Wcast-qual 
CXXFLAGS := -O1 -Wall -Wextra -Wpedantic -Wconversion \
		  -Wcast-align -Wunused -Wold-style-cast \
		  -Wpointer-arith -Wcast-qual 
DBGFLAGS := -g
COBJFLAGS := $(CFLAGS) -c

# path macros
BIN_PATH := bin
OBJ_PATH := obj
SRC_PATH := src
DBG_PATH := debug
WIN_PATH := win

# compile macros
TARGET_NAME := calc
ifeq ($(OS),Windows_NT)
	TARGET_NAME := $(addsuffix .exe,$(TARGET_NAME))
endif
TARGET := $(BIN_PATH)/$(TARGET_NAME)
TARGET_DEBUG := $(DBG_PATH)/$(TARGET_NAME)
TARGET_WIN := $(BIN_PATH)/$(TARGET_NAME).exe

# src files & obj files
SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
OBJ_WIN := $(addprefix $(WIN_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
OBJ_DEBUG := $(addprefix $(DBG_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# clean files list
DISTCLEAN_LIST := $(OBJ) \
                  $(OBJ_DEBUG) \
				  $(OBJ_WIN)
CLEAN_LIST := $(TARGET) \
			  $(TARGET_DEBUG) \
			  $(TARGET_WIN) \
			  $(DISTCLEAN_LIST)

# default rule
default: makedir all

# non-phony targets
$(TARGET): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(CXXFLAGS) 

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CXX) $(COBJFLAGS) -o $@ $< 

$(TARGET_WIN): $(OBJ_WIN)
	$(CXXWIN) -o $@ $(OBJ_WIN) $(CXXFLAGS) 

$(WIN_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CXXWIN) $(COBJFLAGS) -o $@ $< 

$(DBG_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CXX) $(COBJFLAGS) $(DBGFLAGS) -o $@ $<

$(TARGET_DEBUG): $(OBJ_DEBUG)
	$(CXX) -o $@ $(CXXFLAGS) $(DBGFLAGS) $(OBJ_DEBUG) 

# phony rules
.PHONY: makedir
makedir:
	@mkdir -p $(BIN_PATH) $(OBJ_PATH) $(DBG_PATH)

.PHONY: all
all: $(TARGET)

.PHONY: debug
debug: $(TARGET_DEBUG)

.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: debug_run
debug_run: $(TARGET)
	valgrind ./$(TARGET)

.PHONY: win
win: $(TARGET_WIN)

.PHONY: win_run
win_run: $(TARGET_WIN)
	./$(TARGET_WIN)

.PHONY: clean
clean:
	@echo CLEAN $(CLEAN_LIST)
	@rm -f $(CLEAN_LIST)

.PHONY: distclean
distclean:
	@echo CLEAN $(DISTCLEAN_LIST)
	@rm -f $(DISTCLEAN_LIST)