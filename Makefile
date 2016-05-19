# ------------------------------------------------
# Generic Makefile
#
# Author: yanick.rochon@gmail.com
# Date  : 2011-08-10
#
#                thanks to http://stackoverflow.com/users/128940/beta
# ------------------------------------------------

TARGET   = test

CC       = g++
CFLAGS   = -std=c++11 -g -Wall -I.

LINKER   = g++ -o
LFLAGS   = -Wall

SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
rm = rm -f

all: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(LINKER) $@ $(LFLAGS) $(OBJECTS)
	@date

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(BINDIR)
