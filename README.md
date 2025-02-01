<!-- vim:   set ft=markdown tw=80 cc=+1: -->

# Nouveau - FPGA + Z180

This project combines the latest FPGA design from Johns Digital Basement Youtube
videos together with some bleeding edge enhancements to support running the
Tetris game from [Nabu Games](https://github.com/linuxplayground/nabu-games.git)
The project folder is split into FPGA for the FPGA code and then the Z80 code
and needed to compile tetris.  For instructions on how to compile tetris please
read the Readme document in the Tetris Subfolder.

The FPGA code includes he hex for the bootloader rom required to boot CPM from
an SD Card.  This project does not include all the changes for CPM on the
Nouveau.  That can be found here:
[2063-Z80-cpm](https://github.com/Z80-Retro/2063-Z80-cpm)
