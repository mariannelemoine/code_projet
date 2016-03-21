# project name (generate executable with this name)
TARGET   = create_ILP_SCgraph

CC       = g++
# compiling flags here
CFLAGS   = -Wall -Wextra -ansi -pedantic -Iinclude -Wfatal-errors 


# change these to set the proper directories where each files shoould be
SRCDIR   = ./src
INCDIR	 = ./include
OBJDIR   = ./obj
BINDIR   = .

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCDIR)/*.hpp)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(BINDIR)/$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(CFLAGS) $(OBJECTS)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

 #makefile.dep:$(SRC)
#	$(CC) -MM $(SRC) > $@

.PHONEY: clean
clean:
	rm -f $(OBJDIR)/*.o
