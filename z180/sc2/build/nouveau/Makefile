
TOP=../..
# case here has to match the directory name
PROGS=sc2.com \
      slide.com
LIBS=-L$(TOP)/lib -lplatform.lib -ltms.lib -lstdlib.lib -lstrings.lib -lstdio.lib

include Make.rules

.PHONY: all

# make 'all' be the default build target...
all:: $(PROGS)

sc2.com: $(TOP)/src/sc2.z80
	export ZCCCFG=$(TOP)/../z88dk/lib/config
	$(TOP)/../z88dk/bin/z80asm $(LIBS) -I$(TOP)/headers -o$@ -mz180  -l -m -s -b $^

slide.com: $(TOP)/src/slide.z80
	export ZCCCFG=$(TOP)/../z88dk/lib/config
	$(TOP)/../z88dk/bin/z80asm $(LIBS) -I$(TOP)/headers -o$@ -mz180  -l -m -s -b $^


clean::
	find $(TOP) -name "*.lis" -exec rm -f {} \;
	find $(TOP) -name "*.map" -exec rm -f {} \;
	find $(TOP) -name "*.com" -exec rm -f {} \;
	find $(TOP) -name "*.sym" -exec rm -f {} \;
	find $(TOP) -name "*.o" -exec rm -f {} \;

