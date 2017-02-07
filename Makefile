EXE = atlas
TEXE = utest

OBJDIR = bin/
DOCDIR = doc/
INCDIR = inc/
LIBDIR = lib/
SRCDIR = src/
TSTDIR = tst/

INCPATHS = $(LIBDIR) $(LIBDIR)AuD/inc/

# main source files
SRC = $(wildcard $(SRCDIR)*.c)
INC = $(wildcard $(INCDIR)*.h)
OBJ = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRC))

# test source files
ASRC = $(SRC) $(wildcard $(TSTDIR)*.cpp)
TSRC = $(filter-out $(SRCDIR)main.c, $(ASRC))
TOBJ = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(patsubst $(TSTDIR)%.cpp, $(OBJDIR)%.opp, $(TSRC)))

DEP = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.d, $(patsubst $(TSTDIR)%.cpp, $(OBJDIR)%.dpp, $(ASRC)))

# external sources and libraries
EXT = $(LIBDIR)catch.hpp
LIBS = $(LIBDIR)libaud.a

# C compiler and linker flags
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror $(INCPATHS:%=-I %) -D _GNU_SOURCE
LDFLAGS = -lm

# C++ compiler and linker flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror $(INCPATHS:%=-I %)
LXXFLAGS = -lm

# phony targets
.PHONY: all doc test clean destroy

all: $(EXE)

doc: $(SRC) $(INC) | $(DOCDIR)
	doxygen

test: $(TEXE)

clean:
	rm -rf $(OBJDIR) $(EXE) $(TEXE)

destroy: clean
	rm -rf $(DOCDIR) $(LIBDIR)

# main executable
$(EXE): $(OBJ) $(LIBS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

# test executable
$(TEXE): $(TOBJ) $(LIBS)
	$(CXX) $(CXXFLAGS) $^ $(LXXFLAGS) -o $@

# .o file
# $(LIBS) is required for the headers files
$(OBJDIR)%.o: $(SRCDIR)%.c $(LIBS) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# .opp file
# $(LIBS) is required for the headers files
$(OBJDIR)%.opp: $(TSTDIR)%.cpp $(LIBS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEP)

# .d file
$(OBJDIR)%.d: $(SRCDIR)%.c | $(OBJDIR)
	$(CC) -MM $< -MT $(subst .d,.o,$@) > $@

# .dpp file
$(OBJDIR)%.dpp: $(TSTDIR)%.cpp $(EXT) | $(OBJDIR)
	$(CXX) -MM $< -MT $(subst .dpp,.opp,$@) > $@

# folders
$(DOCDIR) $(OBJDIR) $(LIBDIR):
	mkdir $@

# libraries and external sources
$(LIBDIR)catch.hpp: | $(LIBDIR)
	wget -q "https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp" -O $@

$(LIBDIR)AuD/: | $(LIBDIR)
	git clone -q --single-branch "https://github.com/hmfrank/AuD/" $@

$(LIBDIR)libaud.a: $(LIBDIR)AuD/
	$(MAKE) -C $(LIBDIR)AuD/ all
	cp $(LIBDIR)AuD/libaud.a $@
