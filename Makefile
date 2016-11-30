# main program executable
EXE = atlas
# unit test executable
TEST = utest

OBJDIR = bin/
DOCDIR = doc/
LIBDIR = lib/
SRCDIR = src/
TSTDIR = tst/

SRC = $(wildcard $(SRCDIR)*.c)
OBJ = $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

TST = $(wildcard $(TSTDIR)*.cpp)
TSRC = $(filter-out $(SRCDIR)main.c, $(SRC))
TSRC += $(TST)
TOBJ = $(filter-out $(OBJDIR)main.o, $(OBJ))
TOBJ += $(TST:$(TSTDIR)%.cpp=$(OBJDIR)%.opp)

DEP = $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.d)
DEP += $(TST:$(TSTDIR)%.cpp=$(OBJDIR)%.dpp)

# C compiler and linker flags
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror
LDFLAGS =

# C++ compiler and linker flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror
LXXFLAGS =

.PHONY: all doc test clean destroy


all: $(EXE)

doc: | $(DOCDIR)
	doxygen

test: $(TEST)

clean:
	rm -rf $(EXE) $(TEST) $(OBJDIR)

destroy: clean
	rm -rf $(LIBDIR) $(DOCDIR)

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
$(OBJDIR)%.opp: $(TSTDIR)%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEP)

# .d file
$(OBJDIR)%.d: $(SRCDIR)%.c | $(OBJDIR)
	$(CC) -MM $< -MT $(subst .d,.o,$@) -MF $@

# .dpp file
$(OBJDIR)%.dpp: $(TSTDIR)%.cpp | $(OBJDIR)
	$(CXX) -MM -MG $< -MT $(subst .dpp,.opp,$@) | sed 's/ /\\\n/g' | sed 's/^..\//src\/..\//g' | sed 's/.*\/\.\.\///g' > $@ # regex magic

# folders
$(OBJDIR) $(LIBDIR) $(DOCDIR):
	mkdir $@

# catch single header file
$(LIBDIR)catch.hpp: | $(LIBDIR)
	wget "https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp" -O $@
