
    module Letter

buf_lines equ 36
buf_size equ 2 * buf_lines
height equ 9

;buf ds buf_size, 0xaa
buf equ 0xbf00

direction  db Direction.LTR

    module Direction
RTL equ 0
LTR equ 255
    endmodule


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
    add c
    ld c, a
    ld a, (direction)
    cpl
    ld (direction), a
    ret

Blit:
; Blits buffer with a drawn letter into screen coordinates
    call Scr_of_XY
    ld hl, buf
    ld bc, buf_lines * 2
1
    ldi
    ldi
    dec e
    dec e
    inc d

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

Prep:
limit+* ld a, height
    or a
    ret z
    ld e, a

follow_top+*: ld a, height
    or a
    ld a, e
    jr z, 1f
    ld a, height
1   add_hl_a
    dec hl
    ret

LTR:
    call Prep

    ld b, 24
    ld c, 0

ltr_next_line
    push bc
    ld a, (hl)

    dup 6
      rla
      call c, brick_at_bc
      inc b ; next letter
      inc c
      inc c
    edup

    dec hl

    pop bc
    dec b ; next line
    dec b
    dec b

    dec e
    jr nz, ltr_next_line
    ret



RTL:
    call Prep

    ld b, 24
    ld c, 10

rtl_next_line
    push bc
    ld a, (hl)
    rra
    rra

    dup 6
    rra
    call c, brick_at_bc
    inc b ; next letter
    dec c
    dec c
    edup

    dec hl

    pop bc
    dec b ; next line
    dec b
    dec b

    dec e
    jr nz, rtl_next_line
    ret



;  .XX.
;  XX+X
;  X+XX
;  X+XX
;  .XX.

brick_at_bc:

    di
    push af
    push hl
    ld (smc_brick), sp
    ld hl, buf
    ld a, c
    and 0xf8
    rra
    rra
    rra
    add a, b
    add a, b
    add a, l
    ld l, a
    ; hl = buf + x / 8 + y * 2
    ; hl = pointer to our framebuffer byte where the brick will be drawn
    ld (.smc_store), hl
.smc_store+*: ld sp, 0
    ld a, c
    and 6
    rra
    jr z, bit0
    dec a
    jr z, bit2
    dec a
    jp z, bit4

bit6
    pop hl
    ld a, l
    or %00000001
    ld l, a
    ld a, h
    or %10000000
    ld h, a
    push hl
    pop hl

    pop hl
    ld a, l
    or  %00000011
    ld l, a
    ld a, h
    and %01111111
    or  %01000000
    ld h, a
    push hl
    pop hl

    pop hl
    ld a, l
    and %11111110
    or  %00000010
    ld l, a
    ld a, h
    or  %11000000
    ld h, a
    push hl
    pop hl

    pop hl
    ld a, l
    and %11111110
    or  %00000010
    ld l, a
    ld a, h
    or  %11000000
    ld h, a
    push hl
    pop hl

    pop hl
    ld a, l
    or %00000001
    ld l, a
    ld a, h
    or %10000000
    ld h, a
    push hl
    jp brick_ret


bit0
    pop hl
    ld a, l
    or %01100000
    ld l, a
    push hl
    pop hl

    pop hl
    ld a, l
    and %11011111
    or  %11010000
    ld l, a
    push hl
    pop hl

    pop hl
    ld a, l
    and %10111111
    or  %10110000
    ld l, a
    push hl
    pop hl

    pop hl
    ld a, l
    and %10111111
    or  %10110000
    ld l, a
    push hl
    pop hl

    pop hl
    ld a, l
    or  %01100000
    ld l, a
    push hl
    jp brick_ret

bit2
    pop hl
    ld a, l
    or %00011000
    ld l, a
    push hl
    pop hl

    pop hl
    ld a, l
    and %11110111
    or  %00110100
    ld l, a
    push hl
    pop hl

    pop hl
    ld a, l
    and %11101111
    or  %00101100
    ld l, a
    push hl
    pop hl

    pop hl
    ld a, l
    and %11101111
    or  %00101100
    ld l, a
    push hl
    pop hl

    pop hl
    ld a, l
    or  %00011000
    ld l, a
    push hl
    jp brick_ret
    
bit4
    pop hl
    ld a, l
    or %00000110
    ld l, a
    push hl
    pop hl

    pop hl
    ld a, l
    and %11111101
    or  %00001101
    ld l, a
    push hl
    pop hl

    pop hl
    ld a, l
    and %11111011
    or  %00001011
    ld l, a
    push hl
    pop hl

    pop hl
    ld a, l
    and %11111011
    or  %00001011
    ld l, a
    push hl
    pop hl

    pop hl
    ld a, l
    or  %00000110
    ld l, a
    push hl

brick_ret
smc_brick+* ld sp, 0
    ei
    pop hl
    pop af
    ret

    endmodule

