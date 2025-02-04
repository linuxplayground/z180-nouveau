extern putc, puts
extern is_key_pressed, get_char
extern message

    org     0x100

    ld      a,'@'
    call    putc
    ld      a,0x0A
    call    putc
    ld      a,0x0D
    call    putc

    ld      hl,message
    call    puts


    ; now go into a loop repeating whatever is typed
wait_for_key:
    call    is_key_pressed
    or      a
    jr      z,wait_for_key
    jr      z,exit
    call    get_char
    cp      a,0x1b
    jr      z,exit
    call    putc
    jr      wait_for_key
exit:
    jp      0
