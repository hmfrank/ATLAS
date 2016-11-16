INCDIR = inc
SRCDIR = src
BINDIR = bin

INC = $(wildcard $(INCDIR)/*.h)
SRC = $(wildcard $(SRCDIR)/*.c)
BIN = $(SRC:$(SRCDIR)/%.c=$(BINDIR)/%.o)

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra
LDFLAGS =

atlas: $(BIN)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(BINDIR)/%.o: $(SRCDIR)/%.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f atlas test $(BIN)