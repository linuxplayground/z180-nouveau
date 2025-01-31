TOP=.

-include  $(TOP)/Make.local
include $(TOP)/Make.rules

.PHONY: all clean burn world timings

FILES= \
	top.v \
	memory.v \
	iorq_rd_fsm.v \
	iorq_wr_fsm.v \
	pll_25_18432.v \
	debounce.v \
	vdp/vdp.v \
	vdp/tile.v \
	vdp/vgasync.v

DEPS=\
	pinmap-2057.pcf


# FPGA oscillator speed 
OSC_CLK=25
PX_CLK=25

# FREQ is used for the timing nextpnr verification check
FREQ=$(PX_CLK)

all:: top.bin

rom.bin:
	cp ../../../2063-Z80-cpm/boot/firmware.bin rom.bin

%.hex: %.bin
	hexdump -v -e '/1 "%02x\n"' < $< > $@

top.json: $(FILES) $(DEPS)
	$(COMPILE.v) -p "synth_ice40 -top top -json $@" $(FILES)

timing: top.asc
	icetime -tmd $(DEVICE) $^

vgasync_tb.vvp: vgasync_tb.v vgasync.v
	iverilog -o $@ $^

plot: vgasync_tb.vcd
	gtkwave $^

vdp_table_test_tb.vvp: vdp_table_test_tb.v vdp_table_test.v vgasync.v
	iverilog -o $@ $^

plotv: vdp_table_test_tb.vcd
	gtkwave $^

prog: top.bin
	$(FLASH_PROG) $^

pll_25_18432.v:
	icepll -i 25 -o 18.432 -m -n pll_25_18432 > $@

# extra dependancies
top.asc: $(PINMAP)

clean::
	rm -f pll.v
