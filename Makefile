CC  = g++
CFLAGS = -lm -std=c++0x
OBJ = $(addsuffix .o, $(basename $(shell find . -name "*.cpp")))
BIN    = metnum

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o metnum

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(BIN) $(shell find . -name "*.o")
