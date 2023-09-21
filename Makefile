CC = gcc
CFLAGS = 
FILES = main chunk memory debug value vm compiler scanner object table
OBJECTS = $(patsubst %,%.o,$(FILES))
HEADERS = $(patsubst %,%.h,$(FILES))
BINARY = clox

run: $(BINARY)
	./$(BINARY)

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o clox $(OBJECTS)


# %.o: %.c
#	$(CC) $(CFLAGS) -c -o $@ $^

# main.o: common.h chunk.h debug.h
# chunk.o: chunk.h memory.h
# memory.o: memory.h
# debug.o: debug.h chunk.h


clean:
	rm -f $(BINARY) *.o

