; vim: set ft=z80 :
ifndef STDLIB_H
define STDLIB_H

;===============================================================================
; Jumpt to CPM Warm Boot vector
; INPUT: void
; OUTPUT: void
; CLOBBERS: hl, de
;===============================================================================
extern cpm_terminate

;===============================================================================
; Fills memory with a single value.
; INPUT: A = value to fill, HL = start address, BC = count / size
; OUTPUT: void
; CLOBBERS: hl, de
;===============================================================================
extern fillmem

;===============================================================================
; Generate a random number between 0 and 255, based on seed
; INPUT: VOID
; OUTPUT: A = Random Number 0 <=a<=255
; CLOBBERS: AF
;===============================================================================
extern random

endif
