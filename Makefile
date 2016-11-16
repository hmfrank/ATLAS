# main program executable
EXE = atlas
# unit test executable
TEST = utest

SRCDIR = src/
OBJDIR = bin/
LIBDIR = lib/

SRC = $(wildcard $(SRCDIR)*.c)
OBJ = $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)
DEP = $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.d)
TSRC = $(wildcard $(SRCDIR)*.cpp)
TOBJ = $(filter-out $(OBJDIR)main.o, $(OBJ)) $(subst $(SRCDIR),$(OBJDIR),$(subst .cpp,.opp,$(TSRC)))
TDEP = $(subst $(SRCDIR),$(OBJDIR),$(subst .cpp,.dpp,$(TSRC)))

# C compiler and linker flags
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror
LDFLAGS =

# C++ compiler and linker flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror
LXXFLAGS =

.PHONY: all test clean

all: $(EXE)

test: $(TEST)

clean:
	rm -rf $(EXE) $(TEST) $(OBJDIR)

# link atlas
$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

# link unit test
$(TEST): $(TOBJ)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

# .o file
$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# .opp file
$(OBJDIR)%.opp: $(SRCDIR)%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEP)
-include $(TDEP)

# .d file
$(OBJDIR)%.d: $(SRCDIR)%.c | $(OBJDIR)
	$(CC) -MM $< -MT $(subst .d,.o,$@) -MF $@

# .dpp file
$(OBJDIR)%.dpp: $(SRCDIR)%.cpp | $(OBJDIR)
	$(CXX) -MM -MG $< -MT $(subst .dpp,.opp,$@) | sed 's/ /\\\n/g' | sed 's/^..\//src\/..\//g' | sed 's/.*\/\.\.\///g' > $@ # regex magic

# folders
$(OBJDIR) $(LIBDIR):
	mkdir $@

# catch single header file
$(LIBDIR)catch.hpp: | $(LIBDIR)
	wget "https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp" -O $@
