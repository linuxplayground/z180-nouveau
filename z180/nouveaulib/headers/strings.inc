; vim: set ft=z80 :
ifndef STRINGS_H
define STRINGS_H

;===============================================================================
; itoa16 - convert an unsigned 16bit word to ascii.  Adds leading ZEROS
; INPUT: DE pointer to 7 byte buffer for the result including the terminating
;               zero.
;        HL value to convert
; OUTPUT: void
; COBBERS: BC
;===============================================================================
extern itoa16

;===============================================================================
; Returns the length of a zero terminated string buffer.
; INPUT: HL Pointer to zero terminated string buffer
; OUTPUT: BC = Length of string, original value of HL
; CLOBBERS: BC
;===============================================================================
extern str_len

endif
