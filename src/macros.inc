true            equ 255
false           equ 0

breakpoint      macro
@breakpoint
                endm

add_bc_a        macro
                add a, c
                ld c, a
                adc a, b
                sub c
                ld b, a
                endm

add_hl_a        macro
                add a, l
                ld l, a
                adc a, h
                sub l
                ld h, a
                endm

lineinc_de      macro

                ; move down a pixel line
                ; H 0-1-0-y7-y6-y2-y1-y0 l y5-y4-y3-x4-x3-x2-x1-x0

                inc d
                ld a, d
                and 7
                jr nz, .lq
                ld a, e
                add a, 32
                ld e, a
                jr c, .lq
                ld a, d
                sub 8
                ld d, a
.lq
                endm

lineinc_hl      macro

                ; move down a pixel line
                ; H 0-1-0-y7-y6-y2-y1-y0 l y5-y4-y3-x4-x3-x2-x1-x0

                inc h
                ld a, h
                and 7
                jr nz, .lq
                ld a, l
                add a, 32
                ld l, a
                jr c, .lq
                ld a, h
                sub 8
                ld h, a
.lq
                endm


stop            macro
                ld (.nn), a
                ld a, 0x3
                out (254), a
.nn+*:          ld a, 0 ; restore initial a
                di
                halt
                endm

