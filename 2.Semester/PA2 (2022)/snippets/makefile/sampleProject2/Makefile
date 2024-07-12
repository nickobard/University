# ------------------------------------------------------------------
# COMPILER CONFIGURATIONS
# ------------------------------------------------------------------


# Compilation tool and flags
CXX = c++
CXXFLAGS = -ggdb -std=c++17 -Wall -pedantic
# Linking tool and flags
LD = c++
LDFLAGS =


# ------------------------------------------------------------------
# BUILD CONFIGURATIONS
# ------------------------------------------------------------------


# Executable generated after compiling
EXEFILE := program

# Folder where .o , .d and executable file will be generated
BUILD_DIR := build
# Directories where are source files to be compiled and built
SRCS_DIR  := 

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
DEPS := $(OBJS:.o=.d)

# All directories in the SRCS_DIR folder, even if is empty
# is included to compiler to look for header files there
INCLUDE_DIRS := $(shell find $(SRCS_DIR) -type d)


# Add compiler flags with -I prefix to include all directories 
# in sourses directory where headers can be found
INCLUDE_FLAGS := $(addprefix -I,$(INCLUDE_DIRS)) -MMD -MP

# Update current flags with new directories includes
CXXFLAGS := $(INCLUDE_FLAGS) $(CXXFLAGS)


# ------------------------------------------------------------------
# PROJECT BUILD
# ------------------------------------------------------------------


all: compile

compile: $(PATH_TO_EXEFILE)

# Tarfet to create executable form object files
# $^ is same as $(OBJ_FILES)
$(PATH_TO_EXEFILE): $(OBJ_FILES)
	$(LD) $^ $(LDFLAGS) -o $@  

# For every object file compile and create dependency file,
# if no such file is found.
$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

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

clean:
	-rm -r $(BUILD_DIR)

cl: clean

### TO-DO                                |
### everything bellow should be updated  |
###                                      \/

# ------------------------------------------------------------------
# PROJECT SANITIZER
# ------------------------------------------------------------------


fsall: CXXFLAGS += -fsanitize=address
fsall: LDFLAGS  += -fsanitize=address
fsall: all

fsrun: CXXFLAGS += -fsanitize=address
fsrun: LDFLAGS  += -fsanitize=address
fsrun: $(PATH_TO_EXEFILE)
	./$(PATH_TO_EXEFILE)
	

# ------------------------------------------------------------------
# DOXYGEN
# ------------------------------------------------------------------

# Dunno, but &>/dev/null doesn't work
dox: 
	doxygen doc/Doxyfile 1>/dev/null 2>/dev/null

doxpdf:
	make -C doc/latex 1>/dev/null 2>/dev/null
	-rm -f doc/refman.pdf
	-rm cp doc/latex/refman.pdf doc/

doxall: doc docpdf

doxclean:
	-rm -rdf doc/latex
	-rm -rdf doc/html
	-rm -rdf doc/refman.pdf

# ------------------------------------------------------------------
# NDEBUG AND OPTIMIZATIONS
# ------------------------------------------------------------------

nd_cmpl: CXXFLAGS += -D NDEBUG
nd_cmpl: compile

ndo_cmpl: CXXFLAGS = $(CXX) $(CXXFLAGS) -O3 -D NDEBUG
ndo_cmpl: compile
