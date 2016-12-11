# main program executable
EXE = atlas
# unit test executable
TEST = utest

OBJDIR = bin/
DOCDIR = doc/
INCDIR = inc/
LIBDIR = lib/
SRCDIR = src/
TSTDIR = tst/

# external sources
EXT = $(LIBDIR)catch.hpp $(LIBDIR)AvlTree.h $(LIBDIR)AvlTree.c

# source and object file for main executable
INC  = $(wildcard $(INCDIR)*.h)
SRC  = $(wildcard $(SRCDIR)*.c)
SRC += $(filter %.c, $(EXT))
OBJ  = $(filter %.o, $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o))
OBJ += $(filter %.ol, $(SRC:$(LIBDIR)%.c=$(OBJDIR)%.ol))

# source and object files for unit test executable
TST   = $(wildcard $(TSTDIR)*.cpp)
TSRC  = $(filter-out $(SRCDIR)main.c, $(SRC))
TSRC += $(TST)
TOBJ  = $(filter-out $(OBJDIR)main.o, $(OBJ))
TOBJ += $(TST:$(TSTDIR)%.cpp=$(OBJDIR)%.opp)

DEP  = $(filter %.d, $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.d))
DEP += $(filter %.dl, $(SRC:$(LIBDIR)%.c=$(OBJDIR)%.dl))
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
	$(CXX) $(CXXFLAGS) $^ $(LXXFLAGS) -o $@

# .o file
$(OBJDIR)%.o: $(SRCDIR)%.c $(EXT) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# .ol file
$(OBJDIR)%.ol: $(LIBDIR)%.c $(EXT) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# .opp file
$(OBJDIR)%.opp: $(TSTDIR)%.cpp $(EXT) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEP)

# .d file
$(OBJDIR)%.d: $(SRCDIR)%.c $(EXT) | $(OBJDIR)
	$(CC) -MM $< -MT $(subst .d,.o,$@) > $@

# .dl file
$(OBJDIR)%.dl: $(LIBDIR)%.c $(EXT) | $(OBJDIR)
	$(CC) -MM $< -MT $(subst .dl,.ol,$@) > $@

# .dpp file
$(OBJDIR)%.dpp: $(TSTDIR)%.cpp $(EXT) | $(OBJDIR)
	$(CXX) -MM $< -MT $(subst .dpp,.opp,$@) > $@

# folders
$(OBJDIR) $(LIBDIR) $(DOCDIR):
	mkdir $@



# libraries
$(LIBDIR)catch.hpp: | $(LIBDIR)
	wget "https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp" -O $@

$(LIBDIR)AvlTree.h: | $(LIBDIR)
	wget "https://raw.githubusercontent.com/hmfrank/AuD/master/src/AvlTree.h" -O $@

$(LIBDIR)AvlTree.c: | $(LIBDIR)
	wget "https://raw.githubusercontent.com/hmfrank/AuD/master/src/AvlTree.c" -O $@

