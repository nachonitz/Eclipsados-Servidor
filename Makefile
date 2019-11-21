# Source: https://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/

# All of the sources participating in the build are defined here
-include sources.mk
-include src/modelo/nivel/subdir.mk
-include src/modelo/entidadUbicada/dibujable/elemento/subdir.mk
-include src/modelo/entidadUbicada/dibujable/subdir.mk
-include src/modelo/entidadUbicada/subdir.mk
-include src/modelo/subdir.mk
-include src/subdir.mk
-include build/modelo/nivel/subdir.mk
-include build/modelo/entidadUbicada/dibujable/elemento/subdir.mk
-include build/modelo/entidadUbicada/dibujable/subdir.mk
-include build/modelo/entidadUbicada/subdir.mk
-include build/modelo/subdir.mk
-include build/subdir.mk
-include subdir.mk
-include objects.mk

CC := g++ # This is the main compiler
SRCDIR := src
BUILDDIR := build
TARGET := bin/servidor
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g # -Wall
LIB := -pthread -lSDL2 -lSDL2_image -lSDL2_mixer -fno-stack-protector
INC := -I include

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	$(shell for d in `find $(SRCDIR)/* -type d | cut -b 5-`; do mkdir -p $(BUILDDIR)/$$d; done)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
# tester:
#   $(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

.PHONY: clean
