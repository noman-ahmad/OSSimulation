
SRC = src
BUILD = build
BIN = bin

all: $(SRC)
	mkdir $(BUILD) $(BIN)
	cd $(SRC) && make all 

clean: $(SRC)
	cd $(SRC) && make clean
	rmdir $(BIN) 
	rmdir $(BUILD)
