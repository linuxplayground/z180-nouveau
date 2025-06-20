TOP=../..
PROGS=jjack.com
LIBS=-L$(TOP)/lib -lplatform.lib -ltms.lib -lstdlib.lib -lstrings.lib -lstdio.lib

include Make.rules

.PHONY: all

# make 'all' be the default build target...
all:: $(PROGS)

jjack.com: $(TOP)/src/main.z80
	$(Z80ASM) $(LIBS) -I$(TOP)/headers -o$@ -mz180  -l -m -s -b $^

clean::
	find $(TOP) -name *.o -exec rm {} \;
	find $(TOP) -name *.lis -exec rm {} \;
	find $(TOP) -name *.com -exec rm {} \;
	find $(TOP) -name *.map -exec rm {} \;
	find $(TOP) -name *.sym -exec rm {} \;

