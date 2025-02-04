public is_key_pressed, get_char

CNTLA0:                 equ 0x00
CNTLB0:                 equ 0x02
RDR0:                   equ 0x08
ASEXT0:                 equ 0x12
STAT0:                  equ 0x04
TDR0:                   equ 0x06


section MYLIB

is_key_pressed:
      ld      a,0
      in0     a,(CNTLA0)
      and     ~0x08
      out0    (CNTLA0),a
      ld      a,0 
      in0     a,(STAT0)
      and     0b10000000
      ret     z
      ld      a,1
      ret

get_char:
      ld      a,0
      in0     a,(RDR0)
      ret
