prelude macro

    org 0x5ccb
basic_start equ $
basic_length equ End - $

line10:
    db 0, 10
    dw .len
.cmds
    db 0f9h, 0c0h, 0b0h, '"23774"', "\n" ; RANDOMIZE USR VAL "23774"
.len equ $ - .cmds

    db 0, 15 ; line 15, all the code will be stored in this basic line
    dw End - Start
    endm

result_save macro

    display "basic-sta", /A, basic_start
    display "basic-len", /A, basic_length

    display "Saving retroistaba.tap"
    emptytap "retroistaba.tap"
    savetap  "retroistaba.tap", basic, "Retro", basic_start, basic_length, 10

    endm
