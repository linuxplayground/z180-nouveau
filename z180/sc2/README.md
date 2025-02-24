<!-- vim: set tw=80 cc=80: -->
# SC2 Image Viewer for CPM on the Nouveau

First of all lets be crystal clear!  This code will not work on a stock TMS VDP
chip.  It's designed to run efficiently on the Nouveau FPGA project (2057 + 2067).

## SC2

The SC2 format is a screen dump format from the MSX Basic BSAVE and BLOAD
routines.  The format looks like this:

```text
Position 0x0000: 0x0007 Bytes of header information
Position 0x0007: 0x1800 Bytes of pattern data
Position 0x1807: 0x300  Bytes of name table data.  Usually 3 x 256 bytes in
                        ascending order
Position 0x2000: 0x1800 Bytes of color data
```

These positions align with with the graphics mode 2 registers as follows:

```text
        db      0x02,0x80       ; graphics mode 2
        db      0x40,0x81       ; graphics mode 2, enable screen
        db      0x06,0x82       ; name table 0x1800 - 0x1aff
        db      0xff,0x83       ; color table 0x2000 - 0x37ff
        db      0x03,0x84       ; pattern table 0x0000 - 0x17ff
        db      0xff,0x85       ; sprint attribute table 0x3f80 - 0x3fff
        db      0xff,0x86       ; sprint pattern table 0x3800 - 0x3fff
        db      0x36,0x87       ; fg/bg colors

```

So to load an SC2 file, the simplest thing to do is ensure that the VDP
registers are set up according to the above table, read the file to disk, skip
the first 7 bytes and dump the whole file into VDP Memory starting at VRAM
Address 0.

## SC2.COM

This example program very simply relies on CP/M to autopopulate the default FCB
at 0x5C with the commandline filename given.  This FCB is ready to go and can be
used to open the file and sequentially read all the data in it.

This code is very simple and not documented really.  See SLIDE.Z80 for better
comments.

## SLIDE.COM

The show is a bit different.  My approach was to build a list of all the SC2
file names into memory and then iterate through the list performing these steps
on each iteration:

- Make sure all other records in the whole 36 byte long FCB are zero.
- Copy the filename into the default FCB.
- Open the file
- Set the DMA to be the start of a buffer of free memory.
- Call the sequential read operation and update the DMA until the read operation
  fails.
- close the file
- copy all the data in the buffer over to VRAM. (I am copying 0x3800 bytes)

I have tried to document the source code as best as I can.
