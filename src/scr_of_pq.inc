Scr_of_PQ:      ;   B = y 0..23
                ;   C = x 0..31
                ; out:
                ;   DE - screen address
                ; messes up nothing
                ld a, b
                and 0x18
                or 0x40
                ld d, a
                ld a, b
                rrca
                rrca
                rrca
                and $e0
                add c
                ld e, a
                adc a, d
                sub e
                ld d, a
                
                ret

