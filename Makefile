EXE = atlas
TST = utest

DOCDIR = doc/
INCDIR = inc/
SRCDIR = src/

# all .c and .h files
SRC = $(wildcard $(SRCDIR)*.c) $(wildcard $(INCDIR)*.h)

# phony targets
.PHONY: all doc test clean destroy

all: $(EXE)

doc: $(SRC) | $(DOCDIR)
	doxygen

test: $(TST)

clean:
	$(MAKE) -f MakefileAtlas clean
	$(MAKE) -f MakefileTest clean

destroy:
	$(MAKE) -f MakefileAtlas destroy
	$(MAKE) -f MakefileTest destroy
	rm -rf $(DOCDIR)

$(EXE):
	$(MAKE) -f MakefileAtlas $@

$(TST):
	$(MAKE) -f MakefileTest $@

# folders
$(DOCDIR):
	mkdir $@

