       org 003h

section .text

start:
       MOV     AH,5
       MOV     AL,0
       INT     10H ; set current video page to 0
       MOV     AL,2
       MOV     AH,0 ; set video mode to 80x25 BW
       INT     10H
       MOV     BH,0 ; set to current page of 0
       MOV     BL,4
       MOV     CX,1
       MOV     DH,18
       MOV     DL,0
       LEA     SI,[STRI]
NEXT:  MOV     AH,2
       INT     10H
       INC     DX
       MOV     AL,[SI]
       CMP     AL,'$'
       JE      KON
       MOV     AH,9
       INT     10H
       INC     SI
       JMP     SHORT NEXT
KON:   JMP     KON

section .data

STRI   DB      'Hello, world ! $'

