char_full:
        dg xxxxxxxx
        dg xxxxxxxx
        dg xxxxxxxx
        dg xxxxxxxx
        dg xxxxxxxx
        dg xxxxxxxx
        dg xxxxxxxx
        dg xxxxxxxx
        dg xxxxxxxx
char_t:
        dg xxxxxx--
        dg --xx----
        dg --xx----
        dg --xx----
        dg --xx----
        dg --xx----
        dg --xx----
        dg --xx----
        dg --xx----
char_i:
        dg xxxxxx--
        dg --xx----
        dg --xx----
        dg --xx----
        dg --xx----
        dg --xx----
        dg --xx----
        dg --xx----
        dg xxxxxx--
char_e:
        dg xxxxxx--
        dg xx------
        dg xx------
        dg xx------
        dg xxxxx---
        dg xx------
        dg xx------
        dg xx------
        dg xxxxxx--

char_r:
        dg xxxxx---
        dg xx--xx--
        dg xx--xx--
        dg xx--xx--
        dg xxxxx---
        dg xx-xx---
        dg xx--xx--
        dg xx--xx--
        dg xx--xx--

char_o:
        dg -xxxx---
        dg xx--xx--
        dg xx--xx--
        dg xx--xx--
        dg xx--xx--
        dg xx--xx--
        dg xx--xx--
        dg xx--xx--
        dg -xxxx---



; retroistaba
                ; dg -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- 
                ; dg -xxxxx-- -xxxxxx- -xxxxxx- -xxxxx-- --xxxx-- -xxxxxx- --xxxx-- -xxxxxx- ---xx--- -xxxxx-- ---xx--- 
                ; dg -xx--xx- -xx----- ---xx--- -xx--xx- -xx--xx- ---xx--- -xx--xx- ---xx--- --xxxx-- -xx--xx- --xxxx-- 
                ; dg -xx--xx- -xx----- ---xx--- -xx--xx- -xx--xx- ---xx--- -xx----- ---xx--- -xx--xx- -xx--xx- -xx--xx- 
                ; dg -xx--xx- -xx----- ---xx--- -xx--xx- -xx--xx- ---xx--- --xx---- ---xx--- -xx--xx- -xx--xx- -xx--xx- 
                ; dg -xxxxx-- -xxxxx-- ---xx--- -xxxxx-- -xx--xx- ---xx--- ---xx--- ---xx--- -xx--xx- -xxxxx-- -xx--xx- 
                ; dg -xx-xx-- -xx----- ---xx--- -xx-xx-- -xx--xx- ---xx--- ----xx-- ---xx--- -xxxxxx- -xx--xx- -xxxxxx- 
                ; dg -xx--xx- -xx----- ---xx--- -xx--xx- -xx--xx- ---xx--- -----xx- ---xx--- -xx--xx- -xx--xx- -xx--xx- 
                ; dg -xx--xx- -xx----- ---xx--- -xx--xx- -xx--xx- -xxxxxx- -xx--xx- ---xx--- -xx--xx- -xx--xx- -xx--xx- 
                ; dg -xx--xx- -xxxxxx- ---xx--- -xx--xx- --xxxx-- -xxxxxx- --xxxx-- ---xx--- -xx--xx- -xxxxx-- -xx--xx- 

fb_height equ 10
fb_width equ 11
fb_to_end equ fb_width * (fb_height - 1)

framebuffer
                dg -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- 
                dg -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- 
                dg -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- 
                dg -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- 
                dg -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- 
                dg -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- 
                dg -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- 
                dg -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- 
                dg -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- 
                dg -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- -------- 

