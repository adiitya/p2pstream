# Target
LIB 		= libcore.a 


# Directories
INC_DIR 	= ./include
SRC_DIR 	= ./source
OBJ_DIR 	= ./obj


# Tools for building
COM 		= g++
ARCH 		= ar
MAKEDEPEND  = makedepend 


# Flags for building tools
CFLAGS 		= -c -Wall -Wextra -error -std=c++11 -I$(INC_DIR)
ARFLAG 		= -vrcs


# All source file
_SOURCE 	= data.cpp connections.cpp

# Path to source file
SRC_FILE 	= $(_SOURCE:%.cpp=$(SRC_DIR)/%.cpp)

# Path to obj file
OBJ_FILE 	= $(_SOURCE:%.cpp=$(OBJ_DIR)/%.o)

# Dependency file
DEP 		= .depend

#--------------------------------------------------------------------------

lib: $(LIB)

$(LIB): $(OBJ_FILE)
	$(ARCH) $(ARFLAG) $(LIB) $(OBJ_FILE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(COM) $< -o $@ $(CFLAGS)

# Include dependency file for object files
include $(DEP)

# Delete all object file and libcore.a
clean: 
	rm $(OBJ_DIR)/*
	rm $(LIB)

# Generate dependency for object files
depend:
	$(MAKEDEPEND) -Y$(INC_DIR) $(SRC_FILE) -f$(DEP)
	rm $(DEP).bak