GPP= g++
BIN = bin/
OBJ = obj/
INC = include/
SRC = src/
CFLAG = -c
OFLAG = -o
all: server client createObj

server:
	$(GPP) $(OFLAG) $(BIN)server $(SRC)server.cpp $(OBJ)func.o
createObj:
	$(GPP) $(CFLAG) $(OFLAG) $(OBJ)func.o $(SRC)func.cpp

client:
	$(GPP) $(OFLAG) $(BIN)client $(SRC)client.cpp

ss:
	./$(BIN)server
sc:
	./$(BIN)client
clean:
	rm $(OBJ)func.o $(BIN)server $(BIN)client
