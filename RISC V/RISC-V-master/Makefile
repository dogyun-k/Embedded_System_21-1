
CC=gcc
CFLAGS=-c
LFLAGS=-o
TARGET=rv_iss
OBJS=rv_main.o read_program.o utils.o

$(TARGET):$(OBJS)
	$(CC) -o $@ $^

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
