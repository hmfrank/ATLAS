CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror
LDFLAGS =

SRCDIR = src/
OBJDIR = bin/

SRC = $(wildcard $(SRCDIR)*.c)
OBJ = $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)
DEP = $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.d)
EXE = atlas

.PHONY: all clean

all: $(EXE)

# link
$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

# .o file
$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEP)

# .d file
$(OBJDIR)%.d: $(SRCDIR)%.c | $(OBJDIR)
	{ echo -n $(OBJDIR); $(CC) -MM $<; } > $@

# obj-folder
$(OBJDIR):
	mkdir $@

clean:
	rm -rf atlas test $(OBJDIR)
