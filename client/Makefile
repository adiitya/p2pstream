# Target
EXE 		:= client.exe 

# Common makefile
COMMON		:= ../.common

CORE_INC_DIR:= ../core/include

include $(COMMON)

SRC_PATH 	+= main.cpp
SRC_FILE 	+= main.cpp
CFLAGS 		+= -I../core/include

LFLAG 		:= -Wall -Wextra -std=c++11 -lcore -lpthread -L../core

#--------------------------------------------------------------------------

$(EXE): core $(OBJ_PATH)
	$(COM) $(OBJ_PATH) -o $(EXE) $(LFLAG)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(COM) $< -o $@ $(CFLAGS)

obj/main.o: main.cpp
	$(COM) $< -o $@ $(CFLAGS)

core:
	cd ../core &&\
	make

include $(DEP)

clean:
	rm $(EXE) &&\
	rm $(OBJ_DIR)/*	

depend:
	$(MAKEDEPEND) -Y -I$(INC_DIR) -I$(CORE_INC_DIR) $(SRC_PATH) -f$(DEP) &&\
	$(SED) -i 's/source/obj/g' $(DEP) &&\
	rm $(DEP).bak