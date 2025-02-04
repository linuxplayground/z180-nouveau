<!-- vim: set ft=markdown tw=80 cc=80 spell: -->
# Using Z88DK-ASM to Assemble and Link

This little project demonstrates how to declare code in different files with
global exports and imports etc.

Being able to structure code this way provides for a better experience for you
the developer.

Some references:

- https://github.com/z88dk/z88dk/wiki/Tool---z80asm
- https://github.com/z88dk/z88dk/issues/247 - There is some discussion here
about using a single `.asm` file to list out and organise all your sections
into the memory map.

# Where does org 0x100 go

This should be in your main.asm file.  Note that the main body of your code
doesn't actually need to be defined in a section.  The binary files are created
from assembly files that have an org statement in them.

You can generate multiple binaries for multiple sections.  In this example, we
just compile them alltogether.

you can also compile object files independantly of each other and then compile
them all together at the end.  The first of the above links expalins this quite
clearly in the `commandline` section.
