
TOP=../..
# case here has to match the directory name
PROG=text.com
LIBS=-L$(TOP)/lib -lplatform.lib -ltms.lib -lstdlib.lib -lstrings.lib -lstdio.lib

include Make.rules

.PHONY: all

# make 'all' be the default build target...
all:: $(PROG)

$(PROG): $(TOP)/src/main.z80
	export ZCCCFG=$(TOP)/../z88dk/lib/config
	$(Z80ASM) $(LIBS) -I$(TOP)/headers -o$@ -mz180  -l -m -s -b $^

clean::
	rm -f *.com *.lis *.o *.map

