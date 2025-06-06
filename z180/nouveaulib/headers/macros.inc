#ifndef MACROS_H
#define MACROS_H
;===============================================================================
; Add A to HL, result in HL
; INPUT: A = 8bit value to add to HL, HL=value to add to.
; OUTPUT: HL = result of addition.
; CLOBBERS: none
;===============================================================================
    MACRO addhla
        add     a, l    ; A = A+L
        ld      l, a    ; L = A+L
        adc     a, h    ; A = A+L+H+carry
        sub     l       ; A = H+carry
        ld      h, a    ; H = H+carry
    ENDM
    MACRO adddea
        add     a, e    ; A = A+E
        ld      e, a    ; E = A+E
        adc     a, d    ; A = A+E+D+carry
        sub     e       ; A = D+carry
        ld      d, a    ; D = D+carry
    ENDM
;===============================================================================
; Multiplication Macros (powers of 2 only.)
; INPUT: HL, value to multiply
; OUTPUT: HL = result of multiplication
; CLOBBERS: none
;===============================================================================
    MACRO mul4
        add     hl,hl   ;2
        add     hl,hl   ;4
    ENDM

    MACRO mul8
            add     hl,hl   ;2
            add     hl,hl   ;4
            add     hl,hl   ;8
    ENDM

    MACRO mul16
            add     hl,hl   ;2
            add     hl,hl   ;4
            add     hl,hl   ;8
            add     hl,hl   ;16
    ENDM

    MACRO mul32
            add     hl,hl   ;2
            add     hl,hl   ;4
            add     hl,hl   ;8
            add     hl,hl   ;16
            add     hl,hl   ;x32
    ENDM

    ;===============================================================================
    ; Division Macros (powers of 2 only.)
    ; INPUT: A, value to divide
    ; OUTPUT: A = result of division
    ; CLOBBERS: none
    ;===============================================================================
    MACRO div2
            and     0xfe       ; remove the bits that get rotated out
            rra
    ENDM

    MACRO div4
            and     0xfc       ; remove the bits that get rotated out
            rra
            rra
    ENDM

    MACRO div8
            and     0xf8       ; remove the bits that get rotated out
            rra
            rra
            rra
    ENDM

    ;===============================================================================
    ; Memory Management Macros
    ;===============================================================================
    MACRO fillmem start,size,value
            ld      a,value
            ld      hl,start
            ld      bc,size
            call    fillmem
    ENDM

    MACRO inc8 addr
            ld      a,(addr)
            inc     a
            ld      (addr),a
    ENDM

    MACRO inc16 addr
            push    hl
            ld      hl,(addr)
            inc     hl
            ld      (addr),hl
            pop     hl
    ENDM

    MACRO dec8 addr
            ld      a,(addr)
            dec     a
            ld      (addr),a
    ENDM
#endif
