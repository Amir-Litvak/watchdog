TARGET = $(shell basename $(CURDIR))
DEP = dynamic_vector.o

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -pthread
RCFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -pthread
LDFLAGS =  -L$(LIBS_DEBUG) -Wl,-rpath=$(LIBS_DEBUG)
RLDFLAGS = -L$(LIBS_RELEASE) -Wl,-rpath=$(LIBS_RELEASE)
IFLAG = -I../include

LIB = lib

LIBS_DEBUG = ../shared_libs/debug
LIBS_RELEASE = ../shared_libs/release

OBJ_DEBUG = ../obj/debug
OBJ_RELEASE = ../obj/release

.PHONY: all
all: debug release

.PHONY: debug
debug:
	mkdir -p $(LIBS_DEBUG)
	mkdir -p $(OBJ_DEBUG)
	for i in $(patsubst %.o,../%,$(DEP)); do make debug -C $$i; done
	$(CC) $(CFLAGS) $(IFLAG) -c -fpic src/$(TARGET).c -o $(TARGET).o
	mv $(TARGET).o $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $(LIB)$(TARGET).so $(OBJ_DEBUG)/$(TARGET).o
	mv $(LIB)$(TARGET).so $(LIBS_DEBUG)

.PHONY: release
release:
	mkdir -p $(LIBS_RELEASE)
	mkdir -p $(OBJ_RELEASE)
	for i in $(patsubst %.o,../%,$(DEP)); do make release -C $$i; done
	$(CC) $(RCFLAGS) $(IFLAG) -c -fpic src/$(TARGET).c -o $(TARGET).o
	mv $(TARGET).o $(OBJ_RELEASE)
	$(CC) $(RCFLAGS) -shared -o $(LIB)$(TARGET).so $(OBJ_RELEASE)/$(TARGET).o
	mv $(LIB)$(TARGET).so $(LIBS_RELEASE)

.PHONY: test
test: debug
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAG) test/$(TARGET)_test.c -o $(TARGET).out -l$(TARGET) $(patsubst %.o,-l%,$(DEP))

.PHONY: clean
clean:
	for i in $(patsubst %.o,../%,$(DEP)); do make clean -C $$i; done
	rm -fr $(OBJ_DEBUG)
	rm -fr $(OBJ_RELEASE)
	rm -fr $(LIBS_DEBUG)
	rm -fr $(LIBS_RELEASE)
	rm -f $(TARGET).out


# $^ all dependencies
# $< first dependency
# $@ the rule's target name
# % all of this type
