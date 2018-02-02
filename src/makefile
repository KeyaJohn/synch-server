%.o:%.c
	gcc -c $<  -o $@ 
SRC=$(wildcard ./*.c ;)
OBJ=$(patsubst %.c,%.o,$(SRC))
BIN=./main

$(BIN):$(OBJ)
	gcc -g -o $@ $^ -lzlog -pthread -lmysqlclient
clean:
	rm -rf $(OBJ) $(BIN)
