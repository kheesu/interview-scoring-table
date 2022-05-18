CC = gcc
CCFLAGS = -g

TARGET = main.o auxi.o crud.o csv.o

all: main clean

main: $(TARGET)
	$(CC) $(CCFLAGS) -o $@ $^

main.o: header.h

auxi.o: header.h
crud.o: header.h
csv.o: header.h

.PHONY: all clean

clean:
	rm -f $(TARGET) *.o
