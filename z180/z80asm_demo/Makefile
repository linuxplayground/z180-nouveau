
SOURCES = \
	  main.asm \
	  rodata.asm \
	  lib/print.asm \
	  lib/input.asm

.PHONY: all clean

all: clean mkdir main.com

# Assemble AND link
main.com:$(SOURCES)
	export ZCCCFG=../z88dk/lib/config
	ZCCCFG=../z88dk/lib/config ../z88dk/bin/z88dk-z80asm -O=build -o=main.com -b -mz180 -l -m $^

mkdir:
	mkdir -pv build
clean:
	rm -fr build
