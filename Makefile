# Makefile for CDK Binary file reader
# Authored by Logan Jones
# NetID:lsj150230
# CS 3377.002

# Library directory location
LIBDIR =/scratch/perkins/lib

# Header includes location
INCLUDEDIR =/scratch/perkins/include

# Source file names
SRCFILES = main.cc

# Variables for C++ compiler
CXX = g++
CC = $(CXX)
CXXFLAGS = -g -Wall -static
CCFLAGS = $(CXXFLAGS)
CPPFLAGS = -I. -I$(INCLUDEDIR)

# Linker Flags
LDFLAGS = -L. -L$(LIBDIR)
LDLIBS = -lcdk -lcurses

# Project name for backup target
PROJECTNAME = CDKBinReader

# Name of executable
EXECFILE = Program6

# List of object files
OBJS = $(SRCFILES:%.cc=%.o)

# The default target which will create the executable
all: $(EXECFILE)

# Target to clean extra files and get rid of executable
clean:
	rm -f $(OBJS) $(EXECFILE) *~ \#*

# Create the executable from the object files
$(EXECFILE): $(SRCFILES)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@

depend:
	makedepend -- $(CXXFLAGS) -- -Y $(SRCFILES)

# Backup target
backup:
	@make clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename "`pwd`"))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date + '%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcvf $(MKBKUPNAME) ../$(CURDIRNAME) 2> /dev/null
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!
