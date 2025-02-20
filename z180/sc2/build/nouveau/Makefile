
TOP=../..
# case here has to match the directory name
PROGS=sc2.com

include Make.rules

.PHONY: all

# make 'all' be the default build target...
all:: $(PROGS)

sc2.com: $(TOP)/src/main.z80
	export ZCCCFG=$(TOP)/../z88dk/lib/config
	$(TOP)/../z88dk/bin/z80asm -I$(TOP)/lib -I$(PLATFORM_DIR) -o$@ -mz180  -l -s -b $^

clean::
	rm -f *.com *.lis *.o

