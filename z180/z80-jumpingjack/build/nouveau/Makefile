
TOP=../..
# case here has to match the directory name
PROGS=jjack.com
LIBS = stdio \
       stdlib \
       strings \
       tms \
       platform

LIBOBJECTS = $(LIBS:%=%.o)
INCLUDES = -I$(TOP)/lib -I$(PLATFORM_DIR) -I$(TOP)/headers

include Make.rules

.PHONY: all

# make 'all' be the default build target...
all:: $(PROGS)

platform.o:
	export ZCCCFG=$(TOP)/../z88dk/lib/config
	$(TOP)/../z88dk/bin/z80asm $(INCLUDES) -o$@ -mz180 $(TOP)/libnouveau/platform.z80

%.o: $(TOP)/lib/%.z80
	export ZCCCFG=$(TOP)/../z88dk/lib/config
	$(TOP)/../z88dk/bin/z80asm $(INCLUDES) -o=$@ -mz180  $^


nouveau.lib: $(LIBOBJECTS)
	export ZCCCFG=$(TOP)/../z88dk/lib/config
	$(TOP)/../z88dk/bin/z80asm $(INCLUDES) -x$@ -mz180  platform.o $(LIBOBJECTS)

jjack.com: nouveau.lib
	export ZCCCFG=$(TOP)/../z88dk/lib/config
	$(TOP)/../z88dk/bin/z80asm -I$(TOP)/headers -lnouveau.lib -o$@ -mz180 -l -m -s -b $(TOP)/src/main.z80


clean::
	rm -f *.com *.lis *.o *.lib *.bin
	find $(TOP)/ -name "*.o" -exec rm {} \;

