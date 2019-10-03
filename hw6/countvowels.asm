;;=============================================================
;;CS 2110 - Fall 2019
;;Homework 6 - Count the Vowels in a String
;;=============================================================
;;Name:
;;=============================================================

.orig x3000

LD R0, STRING
AND R1, R1, 0 ;; vcount
AND R2, R2, 0 ;; index

COUNTLOOP
ADD R3, R2, R0
LDR R4, R3, 0
BRz FINISH

NOT R5, R4
ADD R5, R5, 1

LD R6, A
ADD R6, R6, R5
BRz ISVOWEL

LD R6, E
ADD R6, R6, R5
BRz ISVOWEL

LD R6, I
ADD R6, R6, R5
BRz ISVOWEL

LD R6, O
ADD R6, R6, R5
BRz ISVOWEL

LD R6, U
ADD R6, R6, R5
BRz ISVOWEL

BRnzp CONTLOOP

ISVOWEL
ADD R1, R1, 1

CONTLOOP
ADD R2, R2, 1
BRnzp COUNTLOOP

FINISH
ST R1, ANSWER
HALT

A .fill x41
E .fill x45
I .fill x49
O .fill x4F
U .fill x55
STRING .fill x4000
ANSWER .blkw 1
.end

.orig x4000
.stringz "TWENTY ONE TEN"
.end
