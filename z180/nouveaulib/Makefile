TOP = .
LIBS = stdio.lib stdlib.lib strings.lib tms.lib nouveau.lib debug.lib
INCLUDES = -Iheaders

.PHONY: all

# make 'all' be the default build target...
all:: $(LIBS)
world:: clean all

%.o: $(TOP)/libsrc/%.z80
	export ZCCCFG=$(TOP)/../z88dk/lib/config
	$(TOP)/../z88dk/bin/z80asm $(INCLUDES) -o=$@ -mz180  $^

%.lib: %.o
	export ZCCCFG=$(TOP)/../z88dk/lib/config
	$(TOP)/../z88dk/bin/z80asm $(INCLUDES) -xlib/$@ -mz180 $^

clean::
	rm -f *.com *.lis *.o *.lib *.bin
	find $(TOP)/ -name "*.o" -exec rm {} \;

