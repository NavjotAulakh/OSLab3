CC = clang
CFLAGS = -Wall -Wextra -std=c99 -g
LFLAGS = 
LIBS = -lm -pthread
SOURCES = sodoku.c
OBJECTS = $(subst .c,.o,$(SOURCES))
BIN = sodoku
.PHONY: clean help

sodoku: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $@ 

%.o : %.c
	$(CC) $(CFLAGS) -c $< 

all : $(BIN)

clean:
	rm -f $(OBJECTS) $(BIN) *~

help:
	@echo "Valid targets:"
	@echo "  clean:  removes .o and binary files"
