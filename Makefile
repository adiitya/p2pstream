CLIENT_DIR 	:= ./client
SERVER_DIR 	:= ./server 
CORE_DIR 	:= ./core 

#---------------------------------------------------

client: 
	cd $(CLIENT_DIR) &&\
	make

server:
	cd $(SERVER_DIR) &&\
	make

core:
	cd $(CORE_DIR) &&\
	make
