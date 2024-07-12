# ------------------------------------------------------------------
# COMPILER CONFIGURATIONS
# ------------------------------------------------------------------


# Compilation tool and flags
CXX = c++
CXXLIBS = -std=c++17
CXXFLAGS = $(CXXLIBS) -Wall -pedantic -ggdb
# Linking tool and flags
LD = c++
LDLIBS  = -lSDL2 -lSDL2_image
LDFLAGS = 


# ------------------------------------------------------------------
# BUILD CONFIGURATIONS
# ------------------------------------------------------------------


# Executable generated after compiling
EXEFILE := program

# Folder where .o , .d and executable file will be generated
BUILD_DIR := build

# Directories where are source files to be compiled and built
SRCS_DIR  := src

# Path where actual executable lies
PATH_TO_EXEFILE := $(BUILD_DIR)/$(EXEFILE)

# Find all .cpp files in source directories to be compiled,
# looking for them recursively
SRC_FILES := $(shell find $(SRCS_DIR) -name '*.cpp')

# For each path to the .cpp file hold path to the identical
# .o file in the build folder
# i.e. src/classes/myclass.cpp will be build/src/classes/myclass.o
# stored in the OBJ_FILES variable
OBJ_FILES := $(SRC_FILES:%.cpp=$(BUILD_DIR)/%.o)

# After fisrt building dependencies will be generated
# and should be included. DEPS variable will store paths
# for all possible (not necessary created yet) .d files
DEPS := $(OBJ_FILES:.o=.d)

# All directories in the SRCS_DIR folder, even if is empty
# is included to compiler to look for header files there
INCLUDE_DIRS := $(shell find $(SRCS_DIR) -type d)


# Add compiler flags with -I prefix to include all directories 
# in sourses directory where headers can be found
INCLUDE_FLAGS := $(addprefix -I,$(INCLUDE_DIRS)) 

# Update current flags with new directories includes
CPPFLAGS := $(INCLUDE_FLAGS) -MMD -MP


# ------------------------------------------------------------------
# PROJECT BUILD
# ------------------------------------------------------------------


all: compile

compile: $(PATH_TO_EXEFILE)
# Tarfet to create executable form object files
# $^ is same as $(OBJ_FILES)
$(PATH_TO_EXEFILE): $(OBJ_FILES)
	$(LD) $(LDFLAGS) $^ -o $@  $(LDLIBS)

# For every object file compile and create dependency file,
# if no such file is found.
$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $ $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)


# ------------------------------------------------------------------
# PROJECT RUN
# ------------------------------------------------------------------


run: $(PATH_TO_EXEFILE)
	./$(PATH_TO_EXEFILE)

valgrind: $(PATH_TO_EXEFILE)
	valgrind ./$(PATH_TO_EXEFILE)

vgr: valgrind


# ------------------------------------------------------------------
# CLEANING
# ------------------------------------------------------------------


clean: cleandoc
	-rm -rf $(BUILD_DIR)

cl: clean


# ------------------------------------------------------------------
# PROJECT ADDRESS SANITIZER
# ------------------------------------------------------------------


fsall: CXXFLAGS += -fsanitize=address
fsall: LDFLAGS  += -fsanitize=address
fsall: all 


# ------------------------------------------------------------------
# DOXYGEN
# ------------------------------------------------------------------


doc: 
	doxygen Doxyfile

cleandoc:
	-rm -rf doc


# ------------------------------------------------------------------
# NDEBUG AND OPTIMIZATIONS
# ------------------------------------------------------------------


ndebug: CXXFLAGS += -D NDEBUG
ndebug: all

ndebugO3: CXXFLAGS = $(CXXLIBS) -O3 -D NDEBUG
ndebugO3: all


# ------------------------------------------------------------------
# PROFILING
# ------------------------------------------------------------------

# Gprof

gpall: CXXLIBS += -pg
gpall: LDFLAGS += -pg
gpall: all

gprofile:
	./$(PATH_TO_EXEFILE)
	mv ./gmon.out $(BUILD_DIR)
	gprof $(PATH_TO_EXEFILE) $(BUILD_DIR)/gmon.out > $(BUILD_DIR)/profile.txt
	less $(BUILD_DIR)/profile.txt

gpread:
	gprof $(PATH_TO_EXEFILE) $(BUILD_DIR)/gmon.out > $(BUILD_DIR)/profile.txt
	less $(BUILD_DIR)/profile.txt

# Callgrind

callgrind: cleancgr
	valgrind --tool=callgrind ./$(PATH_TO_EXEFILE)
	mv callgrind.out.* $(BUILD_DIR)

cleancgr:
	-rm -f $(BUILD_DIR)/callgrind.out.*

kcallgrind: 
	kcachegrind $(BUILD_DIR)/callgrind.out.*


# ------------------------------------------------------------------
# DEBUG
# ------------------------------------------------------------------

dbg:
	gdb $(PATH_TO_EXEFILE)