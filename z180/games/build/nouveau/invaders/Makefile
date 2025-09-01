# Override any of the above settings in your own make.local file

TOP=../../..

# case here has to match the directory name
PROGS=invaders.com

all:: $(PROGS)

include ../Make.rules

SRC_DIR=$(TOP)/invaders

%.com: $(SRC_DIR)/invaders.c
	$(ZCC) $(CFLAGS) $(CPPFLAGS) -o $@ $^

world:: clean all

clean::
	rm -f *.com *.lis *.COM

