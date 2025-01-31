# Override any of the above settings in your own make.local file

TOP=../../..

# case here has to match the directory name
PROGS=tetris.com

all:: $(PROGS)

include ../Make.rules

SRC_DIR=$(TOP)/tetris

%.com: $(SRC_DIR)/tetris.c
	$(ZCC) $(CFLAGS) $(CPPFLAGS) -o $@ $^

world:: clean all

clean::
	rm -f *.com *.lis *.COM

