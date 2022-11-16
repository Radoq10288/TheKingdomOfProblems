BINDIR=bin
OBJDIR=obj
SRCDIR=src

OS=$(shell uname -o)
ifeq ($(OS), Msys)
BINFILE=kingprob.exe
endif
ifeq ($(OS), GNU/Linux)
BINFILE=kingprob
endif

BIN=$(BINDIR)/$(BINFILE)
OBJ=$(OBJDIR)/*.o
CFILES=$(SRCDIR)/*.c

CC=gcc

debug: CFLAGS=-g -pedantic -Wall
debug: build compile

release: CFLAGS=-O2 -Wall
release: build compile

compile: $(BIN)
$(BIN) : $(OBJ)
	$(CC) -o $(BIN) $(OBJ)

build: $(OBJ)
$(OBJ) : $(CFILES)
	$(CC) -c $(CFILES) $(CFLAGS)

	@mkdir -p $(BINDIR)
	@mkdir -p $(OBJDIR)
	@mv *.o $(OBJDIR)/

clean:
	rm $(OBJ) $(BINDIR)/*

distclean: clean
	rmdir $(BINDIR) $(OBJDIR)

run:
	$(BIN)

test: build-test run-test

build-test:
	cd test && $(MAKE)

run-test:
	cd test && $(MAKE) run

clean-test:
	cd test && $(MAKE) clean

distclean-test:
	cd test && $(MAKE) distclean



