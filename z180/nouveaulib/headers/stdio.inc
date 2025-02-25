; vim: set ft=z80 :
ifndef STDIO_H
define STDIO_H

bdos_call:              equ 5
bdos_conout:            equ 2
bdos_conio:             equ 6
bdos_const:             equ 11
bdos_fopen:             equ 15
bdos_fclose:            equ 16
bdos_f_sfirst:          equ 17
bdos_f_snext:           equ 18
bdos_fdelete:           equ 19
bdos_fread:             equ 20
bdos_fwrite:            equ 21
bdos_fmake:             equ 22
bdos_setdma:            equ 26
bdos_gsuid:             equ 32

;===============================================================================
; CP/M Get Key press
; INPUT: void
; OUTPUT: ascii of pressed key in A
; CLOBBERS: BC, DE
;===============================================================================
extern getk

;===============================================================================
; CP/M Write char
; INPUT: ascii value to write in A
; OUTPUT: void
; CLOBBERS: BC, DE
;===============================================================================
extern puts

endif
