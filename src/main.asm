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

Draw_ani:
    ei
    ld hl, steps

1
    ld a, (hl)
    or a
    jp z, Draw_ani

    call Letter.Set_limit

    push hl

    halt

    ld hl, char_r
    call Letter.LTR

    ld bc, 8*3*0
    call Letter.Blit

    ld hl, char_e
    call Letter.LTR

    ld bc, 8*2*1
    call Letter.Blit

    ld hl, char_t
    call Letter.LTR

    ld bc, 8*2*2
    call Letter.Blit

    ld hl, char_r
    call Letter.LTR

    ld bc, 8*2*3
    call Letter.Blit

    ld hl, char_o
    call Letter.LTR

    ld bc, 8*2*4
    call Letter.Blit


    pop hl
    inc hl
    jp 1b



steps
    db 1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 9, 9, 8, 7, 6, 5, 4, 3, 2, 0

    include "letter.inc"
    include "text.inc"

End equ $

    savesna "retroistaba.sna", Start

    emptytap "retroistaba.tap"
    savetap  "retroistaba.tap",basic,"retro",Basic.start,Basic.length,10
    savetap  "retroistaba.tap",code,"retro",Start,End-Start


