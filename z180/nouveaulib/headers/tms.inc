; vim: set ft=z80 :
ifndef TMS_H
define TMS_H

;===============================================================================
; These variables are set by the tms_init_* routines.  You can use them to
; access VDP memory without having to know the details or look them up.
;===============================================================================
extern tms_buffer
extern tms_pattern_table
extern tms_pattern_table_len
extern tms_name_table
extern tms_name_table_len
extern tms_color_table
extern tms_color_table_len
extern tms_sprite_attribute_table
extern tms_sprite_attribute_table_len
extern tms_sprite_pattern_table
extern tms_sprite_pattern_table_len

;===============================================================================
; Initialize the VDP in Graphics Mode 1 mode.
; refer to .tms_init_g1_registers at the end of this file for details.
; Disable all sprites by setting byte 0 in each sprite attribute table to 0xD0
; INPUT: void
; OUTPUT: void
; CLOBBERS: none
;===============================================================================
extern tms_init_g1

;===============================================================================
; Initialize the VDP in Graphics Mode 2 mode.
; refer to .tms_init_g1_registers at the end of this file for details.
; Disable all sprites by setting byte 0 in each sprite attribute table to 0xD0
; INPUT: void
; OUTPUT: void
; CLOBBERS: none
;===============================================================================
extern tms_init_g2

;===============================================================================
; Initialize the VDP in Text mode
; Disable all sprites by setting byte 0 in each sprite attribute table to 0xD0
; INPUT: void
; OUTPUT: void
; CLOBBERS: none
;===============================================================================
extern tms_init_text

;===============================================================================
; Set one of the VDP registers
; INPUT: B = Register to set, C = value to set
; OUTPUT: void
; CLOBBERS: none
;===============================================================================
extern tms_set_register

;===============================================================================
; Write one byte of data to the VDP at the current address.
; includes a delay
; OUTPUT: void
; CLOBBERS: none
;===============================================================================
extern tms_put

;===============================================================================
; Set the backdrop colour.
; INPUT: C = Colour to set [0-15]
; OUTPUT: void
; CLOBBERS: DE
;===============================================================================
extern tms_set_backdrop_color

;===============================================================================
; Set the VDP Address to read from.
; INPUT: de = read address
; OUTPUT: void
; CLOBBERS: none
;===============================================================================
extern tms_set_read_address

;===============================================================================
; Set the VDP Address to write to.
; INPUT: de = write address
; OUTPUT: void
; CLOBBERS: none
;===============================================================================
extern tms_set_write_address

;===============================================================================
; Copy system memory to VDP memory after vblank signal only.
; INPUT: DE = VDP target memory address, HL = host memory address, BC = count
; OUTPUT: void
; CLOBBERS: AF, BC, DE, HL
;===============================================================================
extern tms_write_fast

;===============================================================================
; Copy system memory to VDP memory at any time.
; INPUT: DE = VDP target memory address, HL = host memory address, BC = count
; OUTPUT: void
; CLOBBERS: AF, BC, DE, HL
;===============================================================================
extern tms_write_slow

;===============================================================================
; Set the whole colour table to a single colour.
; INPUT: C = Colour to set [0-15]
; OUTPUT: void
; CLOBBERS: HL, DE
;===============================================================================
extern tms_set_all_colors

;===============================================================================
; Initialize all VDP RAM to 0
; INPUT: void
; OUTPUT: void
; CLOBBERS: DE, HL
;===============================================================================
extern tms_clear_vram

;===============================================================================
; Load color table
; INPUT: HL = Address of first byte of color data data, BC = Number of bytes in
; color table.
; OUTPUT: void
; CLOBBERS: DE
;===============================================================================
extern tms_load_color_table

;===============================================================================
; Load pattern table.
; INPUT: HL = Address of first byte of pattern data, BC = Number of bytes in
; pattern table.
; OUTPUT: void
; CLOBBERS: DE
;===============================================================================
extern tms_load_pattern_table

;===============================================================================
; Writes all Zeros to VDP nameTable
; INPUT: L = value to write, DE = Number of times to write.
; OUTPUT: void
; CLOBBERS: AF, BC, DE, HL
;===============================================================================
extern tms_clear_screen

;===============================================================================
; Writes all Zeros to tms_buffer
; INPUT: void
; OUTPUT: void
; CLOBBERS: AF, BC, DE, HL
;===============================================================================
extern tms_clear_buffer

;===============================================================================
; Flush the tms_buffer in system memory to the VDP nameTable after the vsync
; status is set on the status register.
; INPUT: void
; OUTPUT: void
; CLOBBERS: AF, BC, DE, HL
;===============================================================================
extern tms_flush_buffer

;===============================================================================
; Write a characater to the tms_buffer
; INPUT: D = x, E = Y, A = char
; CLOBBERS: AF
;===============================================================================
extern set_char_at_loc_buf

;===============================================================================
; Get the character in the frame buffer at buffer x,y
; INPUT: D = x, E = Y
; OUPTUT: A = char
; CLOBBERS: AF
;===============================================================================
extern get_char_at_loc_buf

;===============================================================================
; Print zero terminated string at location into buffer.
; INPUT: D = x, E = Y, HL = ptr to string
; OUPTUT: void
; CLOBBERS: AF, BC, DE, HL
;===============================================================================
extern print_at_loc_buf

;===============================================================================
; Prints string pointed by HL to ROW (C) in the center of the line.
; INPUT: HL Pointer to zero terminated string
;         C Row number to write to.
; OUTPUT: A=0 when no erros, A != 0 when erros.
; CLOBBERS: ???
;===============================================================================
extern center_text_in_buf_row

;===============================================================================
; Delay routine - ticked off the vdp interrupt
; INPUT: B number of frames to wait
; OUPTUT: void
; CLOBBERS: none
;===============================================================================
extern tms_delay
endif
