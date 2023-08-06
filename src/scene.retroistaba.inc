    module retroistaba
Init:
    ret

morph:
    ld a, (base_dir)
    cpl
    ld (base_dir), a

    or a
    ret z

    ld a, (Letter.follow_top)
    cpl
    ld (Letter.follow_top), a

    ret


Step:

    call morph

    ld hl, steps

1
    ld a, (hl)
    cp 255
    jr z, Step ; start from the first step

    call Letter.Set_limit

    push hl


base_dir+*: ld a, 0
    ld (Letter.direction), a

    ld b, 6
    ld c, 11
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

    ld b, 11
    ld c, 10

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

    halt

    pop hl
    inc hl
    jp 1b

steps
    db 1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1, 255

    endmodule
