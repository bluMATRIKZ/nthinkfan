CC = gcc
SU = sudo
SRC = nthinkfan.c
BIN = /bin/nthinkfan

all:
	$(SU) $(CC) $(SRC) -o $(BIN)
	$(SU) chmod +x $(BIN)

remove:
	$(SU) rm -f $(BIN)
