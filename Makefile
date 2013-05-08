CC  = g++
CFLAGS = -lm
OBJ = $(addsuffix .o, $(basename $(shell find . -name "*.cpp")))
BIN    = metnum

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o metnum

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(BIN) $(shell find . -name "*.o")
