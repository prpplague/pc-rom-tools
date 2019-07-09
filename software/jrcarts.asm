;JRCarts loader
;jeff leyda
;2014
;jeff@silent.net
;
;Modified by Shaos for PCjr cartridge and NASM (2017)

MAX_GAMES       EQU     7 ; 8
LOAD_SEG        EQU     2000h

        org 0

section .text

        db      55h,0AAh,1 ; check CRC only for first 512 bytes
        jmp     main
        db      6Ah,59h ; 2-byte placeholder for CRC correction

; 0) 0x55 0xAA 0x10 (8192 bytes)  current=0x00000 (0x00100)
; 1) 0x90 0x90 0x10 (8192 bytes)  current=0x01FBF (0x020BF)
; 2) 0x55 0xAA 0x20 (16384 bytes) current=0x03FA8 (0x040A8)
; 3) 0x55 0xAA 0x20 (16384 bytes) current=0x07EA1 (0x07FA1)
; 4) 0x55 0xAA 0x50 (40960 bytes) current=0x0BD2F (0x0BE2F)
; 5) 0x55 0xAA 0x50 (40960 bytes) current=0x144D4 (0x145D4)
; 6) 0x55 0xAA 0x10 (8192 bytes)  current=0x1C3D3 (0x1C4D3)
; 7) 0x55 0xAA 0x10 (8192 bytes)  current=0x1E154 (0x1E254)
; maxzero=8192 nonzero=120109 current=130811 (0x1FFFB)

loadTbl:        db      20h,0,  1h,  0h, ; scubaventure
                db      20h,0, 20h,0BFh, ; mouser
                db      40h,0, 40h,0A8h, ; river raid
                db      40h,0, 7Fh,0A1h, ; pitfall II
                db     0A0h,1, 3Eh, 2Fh, ; demon attack
                db     0A0h,2, 45h,0D4h, ; microsurgeon
                db      20h,2,0C4h,0D3h, ; crossfire
                db      20h,2,0E2h, 54h, ; mine shaft
main:
        mov     ax, cs
        mov     ds, ax

        mov     ax, 2           ; set 80x25
        int     10h
        mov     ax, 500h
        int     10h

        xor     bx, bx          ; page# for these routines
        lea     si, [menuText]
printString:
        lodsb
        cmp     al, 0
        jz      input
        mov     ah, 0eh
        int     10h
        jmp     printString

input:
        xor     ax, ax
        int     16h

        sub     al, 30h         ; make input a value
        cmp     al, MAX_GAMES
        ja      input           ; retry dummy!

        lea     si, [loadTbl]
        shl     al, 1
        shl     al, 1
        xor     ah, ah
        add     si, ax          ; si now points to load info

loadit:
        mov     bx, LOAD_SEG    ; segment to load games into
        mov     es, bx

        mov     ch, [si]        ; size in pages (256 bytes)
        mov     cl, 0           ; cx is now size in bytes
        mov     ah, [si+1]      ; segment magic
        mov     bh, [si+2]      ; higher offset
        mov     bl, [si+3]      ; lower offset

        cmp     ah, 1           ; check if data is too far
        je      next1
        cmp     ah, 2           ; check if data is way too far
        jne     loadit_

        mov     ax,ds
        add     ax,1000h
        mov     ds,ax
        jmp     loadit_

next1:  mov     ax,ds
        add     ax,0800h
        mov     ds,ax

loadit_:
        mov     si,bx
        xor     ax,ax
        mov     di,ax
        mov     bx,ax

loadit_1:
        mov     ah,[si]
        mov     [es:di],ah
        inc     di
        inc     si
        cmp     ah,0
        jne     loadit_2
        inc     bx
        cmp     bx,3
        jne     loadit_3
        mov     bl,[si]
        inc     si
        mov     bh,[si]
        inc     si
        sub     bx,3
        jz      loadit_3
        sub     cx,bx
loadit_1a:
        mov     [es:di],al ; zero
        inc     di
        dec     bx
        jnz     loadit_1a
loadit_2:
        xor     bx,bx
loadit_3:
        dec     cx
        jnz     loadit_1

        xor     ax, ax
        mov     ds, ax
        mov     ax, LOAD_SEG    ; jump to segment:3 to start rom
        mov     bx, 3
        push    ax
        push    bx
        retf

menuText        db "0.Scub "
                db "1.Mous "
                db "2.Rive "
                db "3.Pitf "
                db "4.Dem "
                db "5.Mic "
                db "6.Cro "
                db "7.Min"
                db 0
compressed:
incbin "jrcarts4.bin"
