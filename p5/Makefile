SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)
HEADERS := $(wildcard *.h)
TARGETS := main

COMMON   := -O2 -Wall -Wno-narrowing -DNDEBUG
CFLAGS   := $(CFLAGS) $(COMMON)
CC       := g++
LD       := $(CC)

IMPL := fsm.o
ifdef skel
IMPL := $(IMPL:.o=-skel.o)
endif

all : $(TARGETS)
.PHONY : all

# {{{ for debugging
debug : CFLAGS += -g -DDEBUG=1 -U NDEBUG
debug : $(TARGETS)
.PHONY : debug
# }}}

$(OBJECTS) : %.o : %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGETS) : % : %.o $(IMPL)
	$(LD) -o $@ $^

.PHONY : clean
clean :
	rm -f $(OBJECTS) $(TARGETS) output
