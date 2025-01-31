<!-- vim:   set ft=markdown tw=80 cc=+1: -->
# 2057 FPGA Verilog

These verilog files will set up the 2057 board to work with the 2067 Z180
breakout board.  The CPM Bootloader ROM hex file is included.

It also includes a very simple VDP based loosely on Graphics Mode I of the
TMS9918A.  At this time (2025-01-31) the code does not include sprites, text
mode or graphics mode 2.

The VDP does have a couple of simple enhancements for Graphics Mode 1.  They are
commented in the Verilog should you need them.

The enhancements relate to the colour table.

None of the registers do anything except for writing to register 7 to set the
border colour.

Colour Options:

1. Identical to Graphics I Mode on the TMS9918A.
    - 256 patterns
    - 768 (32x24) tiles
    - border colour on REG 7
    - 16 colours spread across 256 patterns in groups of 8 patterns per entry.
    - First 8 patterns are defined by the first entry in the colour table.
    - Colour table is 32 bytes long.
2. Graphics I mode with single colour per pattern  (DEFAULT)
    - 256 patterns
    - 768 (32x24) tiles
    - border colour on REG 7
    - 16 colours spread across 256 patterns.  One colour per pattern.
    - Colour table is 256 bytes long.
3. Graphics I mode with single colour per name table location.
    - 256 patterns
    - 768 (32x24) tiles
    - border colour on REG 7
    - Colour table is 768 bytes long and each cell in the tile map can be
    assigned its own colour irrespective of pattern.

The second option was chosen for Tetris as this is how the game was designed
originally.

## VGA PINOUT

```text
rgb[0]  64   #red 0
rgb[1]  74   #red 1
rgb[2]  76   #red 2
rgb[3]  79   #red 3
rgb[4]  73   #green 0
rgb[5]  75   #green 1
rgb[6]  78   #green 2
rgb[7]  80   #green 3
rgb[8]  81   #blue 0
rgb[9]  83   #blue 1
rgb[10] 85   #blue 2
rgb[11] 88   #blue 3

hsync   60
vsync   62
```

## Reset Button

On my particular board (due to some careless mistakes made) my FPGA Pin on S1 is
blown.  I have therefore had to use S2 for the reset button.

## Compilation

Compilation is meant to be done on a Raspberry Pi and programmed via the RPI
interface on the 2057 board.

1. Meet all the open-source prerequisites defined here:
   [https://github.com/johnwinans/Verilog-Examples](https://github.com/johnwinans/Verilog-Examples)
2. `make world`
3. `make prog`
