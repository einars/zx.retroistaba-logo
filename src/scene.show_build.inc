    module show_build

; fill up the whole char, brick by brick

Init:
    ld hl, char_ltr
    ld de, char_ltr+1
    ld bc, 9-1
    ld (hl), 0
    ldir

    ld hl, char_rtl
    ld de, char_rtl+1
    ld bc, 9-1
    ld (hl), 0
    ldir

; wait until space pressed
;    ld bc, 0x7ffe
;1
;    in a, (c)
;    and 0x01
;    jr nz, 1b
    ret

Step:
    call step_char_ltr
    call step_char_rtl

    ld a, Letter.Direction.LTR
    ld (Letter.direction), a

    ld c, 10 ; x
    ld b, 12 ; y
    ld hl, char_ltr
    call Letter.Draw
    ld hl, char_rtl
    call Letter.Draw
    halt
    halt
    halt
    halt
    halt
    ret




step_char_ltr:
    ld hl, char_ltr+9

1   dec hl
    ld a, (hl)
    cp 0xaa
    ret z
    cp 0xfc
    jr z, 1b

    scf
    rra
    ld (hl), a
    ret

step_char_rtl:
    ld hl, char_rtl+9
    ;breakpoint

1   dec hl
    ld a, (hl)
    cp 0xaa
    ret z
    and 0xfc
    cp 0xfc
    jr z, 1b


    rrca
    rrca
    scf
    rla
    rlca
    rlca

    ld (hl), a
    ret



    db 0xaa
char_ltr
    db 0, 0, 0, 0, 0, 0, 0, 0, 0

    db 0xaa
char_rtl
    db 0, 0, 0, 0, 0, 0, 0, 0, 0

    endmodule
