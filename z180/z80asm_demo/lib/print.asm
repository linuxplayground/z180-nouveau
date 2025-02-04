; Declare public labels

public putc, puts

bdos_call:              equ 0x0005
bdos_conout:            equ 0x02


; sections are grouped together during linking in the order that they are found
; in.  You can declare the same section name in different files.

SECTION MYLIB
;===============================================================================
; CP/M Write char
; INPUT: ascii value to write in A
; OUTPUT: void
; CLOBBERS: BC, DE
;===============================================================================
putc:
    push    hl
    ld      e,a
    ld      c,bdos_conout
    call    bdos_call
    pop     hl
    ret

;===============================================================================
; CP/M Write string
; INPUT: HL Points to start of null terminated string
; OUTPUT: void
; CLOBBERS: BC, DE
;===============================================================================
puts:
        push    hl
        call    puts_loop
        pop     hl
        ret

puts_loop:
        ld      a,(hl)                  ; get the next byte to send
        or      a
        jr      z,puts_done             ; if A is zero, return
        ld      c,a
        call    putc 
        inc     hl                      ; point to next byte to write
        jp      puts_loop
puts_done:
        ret
