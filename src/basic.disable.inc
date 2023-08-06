prelude macro

    org 0xc000

    endm

result_save macro

    display "Saving retroistaba.sna"
    savesna "retroistaba.sna", Start

    endm
