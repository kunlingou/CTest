

mov ax, 18 // AX = 18
mov ah, 78 // AH = 78
add ax,8   // AX = AX + 8
mov ax, bx // AX = BX
add ax, bx // AX = AX + BX

ax = 00C5H
bx = 4026H

add al, 93H // ax = 0058H 并不是真的丢失，放到了其他地方

add ax, 93H // ax = 0158H