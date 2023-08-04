    device zxspectrum48

    include "macros.inc"

    org 0x5ccb
basic_start equ $
basic_length equ End - $

line10:
    db 0, 10
    dw .len
.cmds
    ;db 0f9h, 0c0h, 0b0h, '"49152"', "\n" ; RANDOMIZE USR VAL "49152"
    db 0f9h, 0c0h, 0b0h, '"23774"', "\n" ; RANDOMIZE USR VAL "49152"
.len equ $ - .cmds

    db 0, 15
    dw End - Start


    ;org 0c000h

Start:
    jp 1f

    ei ; made in Latvia
    di
    rst 0

1   
    call Clear
    call Draw_ani

    di
    halt

Clear:
    ld hl, 0x4000
    ld de, 0x4001
    ld bc, 6144
    ld (hl), 0
    ldir
    ld (hl), 7*8 + 0
    ld bc, 767
    ldir
    ret


base_dir db 0

Draw_ani:
    ei
    ld hl, steps

    ld a, 0
    ld (Letter.follow_top), a

    ld a, (base_dir)
    cpl
    ld (base_dir), a

1
    ld a, (hl)
    cp 255
    jp z, Draw_ani

    call Letter.Set_limit

    push hl

    halt

    ld a, (base_dir)
    ld (Letter.direction), a

    ld b, 6*8
    ld c, 11*8
    ld hl, char_r
    call Letter.Draw

    ld hl, char_e
    call Letter.Draw

    ld hl, char_t
    call Letter.Draw

    ld hl, char_r
    call Letter.Draw

    ld hl, char_o
    call Letter.Draw

    ld b, 11*8
    ld c, 10*8

    ld hl, char_i
    call Letter.Draw
    ld hl, char_s
    call Letter.Draw
    ld hl, char_t
    call Letter.Draw
    ld hl, char_a
    call Letter.Draw
    ld hl, char_b
    call Letter.Draw
    ld hl, char_a
    call Letter.Draw

    pop hl
    inc hl
    jp 1b



steps
    db 1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1, 255

    include "letter.inc"
    include "text.inc"
    include "scr_of_xy.short.inc"


End equ $

    display "start:         ",/A, Start
    display "top:           ",/A, $
    display "everything:    ",/A, ($ - Start)
    display "free at least: ",/D, (0xc000 - $)

    ;savesna "retroistaba.sna", Start
    display "basic-sta", /A, basic_start
    display "basic-len", /A, basic_length

    emptytap "retroistaba.tap"
    savetap  "retroistaba.tap", basic, "Retro", basic_start, basic_length, 10


