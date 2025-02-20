TOP=../..
PROGS=jjack.com
LIBS=-L$(TOP)/lib -lplatform.lib -ltms.lib -lstdlib.lib -lstrings.lib -lstdio.lib

include Make.rules

.PHONY: all

# make 'all' be the default build target...
all:: $(PROGS)

jjack.com: $(TOP)/src/main.z80
	export ZCCCFG=$(TOP)/../z88dk/lib/config
	$(TOP)/../z88dk/bin/z80asm $(LIBS) -I$(TOP)/headers -o$@ -mz180  -l -m -s -b $^

clean::
	rm -f *.com *.lis *.o

