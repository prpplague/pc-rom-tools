       org 100h

section .text

start:
       MOV     BH,7 ; 0 for DOSBox
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

