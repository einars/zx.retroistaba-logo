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
    ld (lim), a
    ret


LTR:
    push hl
    call Clear_buf
    pop hl

lim+*: ld a, 9
    or a
    ret z

    ;ld b, a
    ld b, 9
1   inc hl
    djnz 1b
    dec hl

    ld b, 24
    ld c, 0

next_line
    ld (cur_line), a
    push bc
    ld a, (hl)

    ld d, a
    ld e, 6 ; bits to print

next_bit:
    rl d
    jr nc, skip_bit

; draw bit in buffer, at [b c] pixel coordinates
    ; highly unoptimized
    push bc
    push hl
    push de
    inc c  ; 1
    call pix
    inc c
    call pix
    inc c
    inc b ; 2
    call pix
    dec c
    call clr
    dec c
    call pix
    dec c
    call pix
    inc b ; 3
    call pix
    inc c
    call clr
    inc c
    call pix
    inc c
    call pix
    inc b ; 4
    call pix
    dec c
    call pix
    dec c
    call clr
    dec c
    call pix
    inc b ; 5
    inc c
    call pix
    inc c
    call pix

    pop de
    pop hl
    pop bc

skip_bit

    inc b ; next letter
    inc c
    inc c

    dec e
    jr nz, next_bit

    dec hl

    pop bc
    dec b ; next line
    dec b
    dec b
    ld c, 0

    ld a, (cur_line)
    dec a
    ret z
    jp next_line

pix
    ld e, b
    ld d, 0
    ld hl, buf
    add hl, de
    add hl, de
    ld a, c
    and 0xf8
    rra
    rra
    rra
    add_hl_a ; HL = address in buffer

    ld de, bitses
    ld a, c
    and 7
    ld e, a
    ld a, (de)
    or (hl)
    ld (hl), a
    ret

clr
    ld e, b
    ld d, 0
    ld hl, buf
    add hl, de
    add hl, de
    ld a, c
    and 0xf8
    rra
    rra
    rra
    add_hl_a ; HL = address in buffer

    ld de, bitses
    ld a, c
    and 7
    ld e, a
    ld a, (de)
    cpl
    and (hl)
    ld (hl), a
    ret

    endmodule

