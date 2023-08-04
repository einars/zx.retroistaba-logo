    device zxspectrum48

    module Basic
start
    db 0, 10
    dw length
    db 0efh, '""', 0afh, ":" ; LOAD "" CODE
    db 0f9h, 0c0h, 0b0h, '"49152"', "\n" ; RANDOMIZE USR VAL "49152"
length equ $ - start
    endmodule

    org 0c000h

Start:
    jp 1f

    ei
    di
    rst 0
    db "Made in Latvia"

    include "util.inc"

1   
    call Clear
    ;call Draw_frame
    call Draw_ani

    di
    halt

Clear:
    ld hl, 0x4000
    ld de, 0x4001
    ld bc, 6144
    ld (hl), a
    ldir
    ld (hl), 7*8
    ld bc, 767
    ldir
    ret


Draw_frame:
    
    ld hl, char_r
    call Letter.LTR


    ld bc, 0x0000
    call Letter.Blit
    ret

base_dir db 0

Draw_ani:
    ei
    ld hl, steps

    ld a, 0
    ld (Letter.follow_top), 0

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

    ld bc, (6 + 0) * 8 * 256 + 8*11
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

    ld bc,  (6 + 5) * 8 * 256 + 8*10
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

End equ $

    savesna "retroistaba.sna", Start

    emptytap "retroistaba.tap"
    savetap  "retroistaba.tap",basic,"Retro",Basic.start,Basic.length,10
    savetap  "retroistaba.tap",code,"Istaba",Start,End-Start


