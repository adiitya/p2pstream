# Target
LIB 		:= libcore.a 
COMMON		:= ../.common

include $(COMMON)


#--------------------------------------------------------------------------


lib: $(LIB)

$(LIB): $(OBJ_PATH)
	$(ARCH) $(ARFLAG) $(LIB) $(OBJ_PATH)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(COM) $< -o $@ $(CFLAGS)

# Include dependency file for object files
include $(DEP)

# Delete all object file and libcore.a
clean: 
	rm $(OBJ_DIR)/* &&\
	rm $(LIB)

# Generate dependency for object files
depend:
	$(MAKEDEPEND) -Y -I$(INC_DIR) $(SRC_PATH) -f$(DEP) &&\
	$(SED) -i 's/source/obj/g' $(DEP) &&\
	rm $(DEP).bak