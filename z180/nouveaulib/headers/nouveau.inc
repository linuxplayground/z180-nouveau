; vim: set ft=z80 :
ifndef NOUVEAU_H
define NOUVEAU_H

; constants
io_tmsdata              equ 0x80
io_tmslatch             equ 0x81

; Thes are the pin assignments on the joystick ports.
joy_map_left:           equ %00000100
joy_map_right:          equ %00100000
joy_map_up:             equ %10000000
joy_map_down:           equ %01000000
joy_map_button:         equ %00000001


;===============================================================================
; Check if a key was pressed
; INPUT: void
; OUTPUT: A = 1 when a key is pressed, A = 0 when no key pressed.
; CLOBBERS: IY
;===============================================================================
extern is_key_pressed

;===============================================================================
; Gets latest character entered.  DOES NOT BLOCK ON RETRO
; INPUT: void
; OUTPUT: Ascii value of key in A
; CLOBBERS: IY, BC
;===============================================================================
extern get_char

;===============================================================================
; Returns the Joystick Status that can be matched against the Joystick enums
; defined at the beginning of this file.
; INPUT: A 0 = joy0, !0 = joy1
; OUTPUT: joy_status
; CLOBBERS: none
;===============================================================================
extern get_joy_status

; The get_joy_status function populates this variable with the status.
extern joy_status

;===============================================================================
; Wait for the VDP VSYNC status to appear on the status register
; INPUT: void
; OUTPUT: void
; CLOBBERS: AF
;===============================================================================
extern tms_wait

; on the nouveau these functions are all empty.  They are here for compatibility
; that would allow code that calls these functions to be compiled for the nouveau.
extern init
extern ay_read
extern ay_write
extern ay_all_off
extern ay_set_mixer
extern ay_set_tone_volume
extern ay_set_noise_volume
extern ay_play_note_delay
extern ay_play_noise_delay
 
endif
