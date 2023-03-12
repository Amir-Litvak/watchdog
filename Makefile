TARGET = $(shell basename $(CURDIR))
DEP = scheduler.o priority_queue.o heap.o dynamic_vector.o task.o uid.o semaphores.o

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -pthread
RCFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -pthread
LDFLAGS = -L$(DEP_LIBS_DEBUG) -L$(LIBS_DBUG) -Wl,-rpath=$(DEP_LIBS_DEBUG) -Wl,-rpath=$(LIBS_DBUG)
RLDFLAGS = -L$(DEP_LIBS_RELEASE) -L$(LIBS_RELE) -Wl,-rpath=$(DEP_LIBS_RELEASE) -Wl,-rpath=$(LIBS_RELE)
IFLAG = -I include -I lib/include

LIB = lib

LIBS_DBUG = wd_shared_lib/debug
LIBS_RELE = wd_shared_lib/release
DEP_LIBS_DEBUG = lib/shared_libs/debug
DEP_LIBS_RELEASE = lib/shared_libs/release

OBJ_DBUG = obj/debug
OBJ_RELE = obj/release


.PHONY: all
all: debug release test runtest

.PHONY: debug
debug:
	mkdir -p $(LIBS_DBUG)
	mkdir -p $(OBJ_DBUG)
	for i in $(patsubst %.o,lib/%,$(DEP)); do make debug -C $$i; done
	$(CC) $(CFLAGS) $(IFLAG) -c -fpic src/$(TARGET).c -o $(TARGET).o
	mv $(TARGET).o $(OBJ_DBUG)
	$(CC) $(CFLAGS) -shared -o $(LIB)$(TARGET).so $(OBJ_DBUG)/$(TARGET).o
	mv $(LIB)$(TARGET).so $(LIBS_DBUG)
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAG) src/$(TARGET)_proc.c -o $(TARGET)_proc.out -l$(TARGET) $(patsubst %.o,-l%,$(DEP))

.PHONY: release
release:
	mkdir -p $(LIBS_RELE)
	mkdir -p $(OBJ_RELE)
	for i in $(patsubst %.o,lib/%,$(DEP)); do make release -C $$i; done
	$(CC) $(RCFLAGS) $(IFLAG) -c -fpic src/$(TARGET).c -o $(TARGET).o
	mv $(TARGET).o $(OBJ_RELE)
	$(CC) $(RCFLAGS) -shared -o $(LIB)$(TARGET).so $(OBJ_RELE)/$(TARGET).o
	mv $(LIB)$(TARGET).so $(LIBS_RELE)
	$(CC) $(RCFLAGS) $(RLDFLAGS) $(IFLAG) src/$(TARGET)_proc.c -o $(TARGET)_proc.out -l$(TARGET) $(patsubst %.o,-l%,$(DEP))

.PHONY: test
test: debug
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAG) test/$(TARGET)_test.c -o $(TARGET)_test.out -l$(TARGET) $(patsubst %.o,-l%,$(DEP))

.PHONY: runtest
runtest:
	./$(TARGET)_test.out

.PHONY: clean
clean:
	for i in $(patsubst %.o,lib/%,$(DEP)); do make clean -C $$i; done
	rm -fr $(OBJ_DBUG)
	rm -fr $(OBJ_RELE)
	rm -fr $(LIBS_DBUG)
	rm -fr $(TARGET)_test.out


# $^ all dependencies
# $< first dependency
# $@ the rule's target name
# % all of this type
