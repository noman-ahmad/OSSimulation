
SRC = src

all: $(SRC)
	cd $(SRC) && make all 

clean: $(SRC)
	cd $(SRC) && make clean
