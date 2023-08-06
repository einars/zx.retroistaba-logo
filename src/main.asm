    device zxspectrum48

    include "macros.inc"

    ;include "basic.enable.inc" ; create compact retroistaba.tap, all packed into basic code
    include "basic.disable.inc" ; create generic retroistaba.sna, faster debugging, simpler breakpoints etc

    prelude

Start:
    jp 1f

    ei ; made in Latvia
    di
    rst 0

1   
    ei
    call Clear

    call Scene.retroistaba.Init
    ld hl, Scene.retroistaba.Step
    jp call_forever

    ;call Scene.show_build.Init
    ;ld hl, Scene.show_build.Step
    ;jp call_forever


call_forever:
    ld (.s + 1), hl
.s  call 0
    jr .s


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


Draw_ani:




    include "letter.inc"
    include "text.inc"
    ;include "scr_of_xy.short.inc"
    include "scr_of_pq.inc"

    module Scene
    include "scene.show_build.inc"
    include "scene.retroistaba.inc"
    endmodule


End equ $

    display "start:         ",/A, Start
    display "top:           ",/A, $
    display "everything:    ",/A, ($ - Start)


    result_save
