Letter_height equ 9

    module Letter

        align 256
bitses  dg x-------
        dg -x------
        dg --x-----
        dg ---x----
        dg ----x---
        dg -----x--
        dg ------x-
        dg -------x

buf_lines equ 36
buf_size equ 2 * buf_lines
buf ds buf_size, 0xaa
cur_line db 0xaa

Clear_buf:
    ld hl, buf
    ld de, buf + 1
    ld bc, buf_size - 1
    ld (hl), 0
    ldir
    ret

Draw:
    push bc
    push hl
    call Clear_buf
    pop hl
    pop bc

    push bc
    ld a, (direction)
    or a
    jr z, draw_rtl
    call LTR
    jr 1f
draw_rtl
    call RTL
1   pop bc

    push bc
    call Blit
    pop bc
    ld a, 16
    add a, c
    ld c, a
    adc a, b
    sub c
    ld b, a
    ld a, (direction)
    cpl
    ld (direction), a
    ret ; bc = bc + 16

Blit:
; Blits buffer with a drawn letter into screen coordinates
    call Scr_of_XY
    ld hl, buf
    ld bc, 2*buf_lines
1
    ldi
    ldi
    dec e
    dec e
    lineinc_de
    ld a, b
    or c
    jr nz, 1b
    ret

Set_limit:
    ld (limit), a
    ret

    module Direction
    RTL equ 0
    LTR equ 255
    endmodule

direction db Direction.LTR
limit db 9
follow_top db 0 ; boolean: when limit != 9, draw either the top lines, or bottom

LTR:
    ld a, (limit)
    or a
    ret z
    ld b, a

    ld a, (follow_top)
    or a
    ld a, b
    jr z, 1f
    ld a, 9
1   add_hl_a
    dec hl

    ld a, b

    ld b, 24
    ld c, 0

ltr_next_line
    ld (cur_line), a
    push bc
    ld a, (hl)

    ld d, a
    ld e, 6 ; bits to print

ltr_next_bit:
    rl d
    jr nc, ltr_skip_bit

    push hl
    call brick_at_bc
    pop hl

ltr_skip_bit

    inc b ; next letter
    inc c
    inc c

    dec e
    jr nz, ltr_next_bit

    dec hl

    pop bc
    dec b ; next line
    dec b
    dec b
    ld c, 0

    ld a, (cur_line)
    dec a
    ret z
    jp ltr_next_line



RTL:
    ld a, (limit)
    or a
    ret z
    ld b, a

    ld a, (follow_top)
    or a
    ld a, b
    jr z, 1f
    ld a, 9
1   add_hl_a
    dec hl

    ld a, b

    ld b, 24
    ld c, 10

rtl_next_line
    ld (cur_line), a
    push bc
    ld a, (hl)

    rra
    rra
    ld d, a
    ld e, 6 ; bits to print

rtl_next_bit:
    rr d
    jr nc, rtl_skip_bit

    push hl
    call brick_at_bc
    pop hl

rtl_skip_bit

    inc b ; next letter
    dec c
    dec c

    dec e
    jr nz, rtl_next_bit

    dec hl

    pop bc
    dec b ; next line
    dec b
    dec b
    ld c, 10

    ld a, (cur_line)
    dec a
    ret z
    jp rtl_next_line



;  .XX.
;  XX+X
;  X+XX
;  X+XX
;  .XX.

brick_at_bc:
    ld hl, buf
    ld a, c
    and 0xf8
    rra
    rra
    rra
    add a, b
    add a, b
    add a, l
    ld l, a ; hl = base screen address
    ld a, c
    and 6
    rra
    jr z, bit0
    dec a
    jr z, bit2
    dec a
    jr z, bit4

bit6
    ld a, (hl)
    or %00000001
    ld (hl), a
    inc hl
    ld a, (hl)
    or %10000000
    ld (hl), a
    inc hl

    ld a, (hl)
    or  %00000011
    ld (hl), a
    inc hl
    ld a, (hl)
    and %01111111
    or  %01000000
    ld (hl), a
    inc hl

    ld a, (hl)
    and %11111110
    or  %00000010
    ld (hl), a
    inc hl
    ld a, (hl)
    or  %11000000
    ld (hl), a
    inc hl

    ld a, (hl)
    and %11111110
    or  %00000010
    ld (hl), a
    inc hl
    ld a, (hl)
    or  %11000000
    ld (hl), a
    inc hl

    ld a, (hl)
    or %00000001
    ld (hl), a
    inc hl
    ld a, (hl)
    or %10000000
    ld (hl), a
    inc hl

    ret

bit0
    ld a, (hl)
    or %01100000
    ld (hl), a
    inc hl
    inc hl
    ld a, (hl)
    and %11011111
    or  %11010000
    ld (hl), a
    inc hl
    inc hl
    ld a, (hl)
    and %10111111
    or  %10110000
    ld (hl), a
    inc hl
    inc hl
    ld a, (hl)
    and %10111111
    or  %10110000
    ld (hl), a
    inc hl
    inc hl
    ld a, (hl)
    or  %01100000
    ld (hl), a
    ret

bit2
    ld a, (hl)
    or %00011000
    ld (hl), a
    inc hl
    inc hl
    ld a, (hl)
    and %11110111
    or  %00110100
    ld (hl), a
    inc hl
    inc hl
    ld a, (hl)
    and %11101111
    or  %00101100
    ld (hl), a
    inc hl
    inc hl
    ld a, (hl)
    and %11101111
    or  %00101100
    ld (hl), a
    inc hl
    inc hl
    ld a, (hl)
    or  %00011000
    ld (hl), a
    ret
    
bit4
    ld a, (hl)
    or %00000110
    ld (hl), a
    inc hl
    inc hl
    ld a, (hl)
    and %11111101
    or  %00001101
    ld (hl), a
    inc hl
    inc hl
    ld a, (hl)
    and %11111011
    or  %00001011
    ld (hl), a
    inc hl
    inc hl
    ld a, (hl)
    and %11111011
    or  %00001011
    ld (hl), a
    inc hl
    inc hl
    ld a, (hl)
    or  %00000110
    ld (hl), a
    ret
    endmodule

