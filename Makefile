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

# stuff to download and libraries
DNL = $(LIBDIR)catch.hpp $(LIBDIR)AuD/
INC = $(LIBDIR) $(LIBDIR)AuD/inc/
LIBS = $(LIBDIR)libaud.a

# source and object file for main executable
SRC  = $(wildcard $(SRCDIR)*.c)
OBJ  = $(filter %.o, $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o))

# source and object files for unit test executable
TSRC  = $(filter-out $(SRCDIR)main.c, $(SRC))
TSRC += $(wildcard $(TSTDIR)*.cpp)
TOBJ  = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(patsubst $(TSTDIR)%.cpp, $(OBJDIR)%.opp, $(TSRC)))

DEP  = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.d, $(patsubst $(TSTDIR)%.cpp, $(OBJDIR)%.dpp, $(TSRC)))
DEP += $(OBJDIR)main.d

# C compiler and linker flags
CC = gcc
CFLAGS = -std=c99 -g -Wall -Wextra -Werror $(INC:%=-I %) -D _GNU_SOURCE
LDFLAGS =

# C++ compiler and linker flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror $(INC:%=-I %)
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
$(EXE): $(OBJ) $(LIBS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

# link unit test
$(TEST): $(TOBJ) $(LIBS)
	$(CXX) $(CXXFLAGS) $^ $(LXXFLAGS) -o $@

# .o file
$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# .opp file
$(OBJDIR)%.opp: $(TSTDIR)%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEP)

# .d file
$(OBJDIR)%.d: $(SRCDIR)%.c $(DNL) | $(OBJDIR)
	$(CC) -MM $< -MT $(subst .d,.o,$@) > $@

# .dpp file
$(OBJDIR)%.dpp: $(TSTDIR)%.cpp $(DNL) | $(OBJDIR)
	$(CXX) -MM $< -MT $(subst .dpp,.opp,$@) > $@

# folders
$(OBJDIR) $(LIBDIR) $(DOCDIR):
	mkdir $@



# libraries
$(LIBDIR)catch.hpp: | $(LIBDIR)
	wget -q "https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp" -O $@

$(LIBDIR)AuD/: | $(LIBDIR)
	git clone -q --single-branch "https://github.com/hmfrank/AuD/" $@

$(LIBDIR)libaud.a: $(LIBDIR)AuD/
	$(MAKE) -C $(LIBDIR)AuD/
	cp $(LIBDIR)AuD/libaud.a $@
