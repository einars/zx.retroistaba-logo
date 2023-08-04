Scr_of_XY:      ;   B = y (0..191)
                ;   C = x (0..255)
                ; out:
                ;   DE - screen address
                ;   A - scroll offset
                ; messes up:
                ;   nothing
                ld a,b
                rra
                rra
                rra
                and %00011000
                or %01000000
                ld d,a
                ld a,b
                and 7
                or d
                ld d,a
                ld a,b
                rla
                rla
                and %11100000
                ld e,a
                ld a,c
                rra
                rra
                rra
                and %00011111
                or e
                ld e,a
                ld a, c
                and 7
                ret
