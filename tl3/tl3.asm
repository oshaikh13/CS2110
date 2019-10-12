;;=============================================================
;;CS 2110 - Fall 2019
;;Timed Lab 3 - Character Search
;;=============================================================
;;Name: 
;;=============================================================

.orig x3000
LD R0, STRING
AND R1, R1, 0 ;; index

LDR R2, R0, 0 ;; first char
LD R3, LOWER_A ;; lower
LD R7, CHAR

NOT R2, R2 ;; - first char
ADD R2, R2, 1

ADD R4, R2, R3
BRp UPPERSTR
BRnz LOWERSTR

UPPERSTR
AND R5, R5, 0
ADD R5, R5, 1
ST R5, CHKCASE
LD R6, TOUPPER
ADD R7, R6, R7 
BR LOOPCONVERT


LOWERSTR
AND R5, R5, 0
ST R5, CHKCASE
BR LOOPCONVERT


LOOPCONVERT
ADD R6, R1, R0
LDR R6, R6, 0
BRz FINISH

NOT R6, R6
ADD R6, R6, 1
ADD R6, R6, R7
BRz SWITCH
BR INCRLOOP

SWITCH
;; revert
ADD R6, R1, R0
LDR R6, R6, 0

ADD R5, R5, 0
BRp ADDSTORE
BRz SUBSTORE

SUBSTORE
LD R2, TOUPPER
ADD R6, R6, R2
ADD R2, R1, R0
STR R6, R2, 0
BR INCRLOOP

ADDSTORE
LD R2, TOLOWER
ADD R6, R6, R2
ADD R2, R1, R0
STR R6, R2, 0
BR INCRLOOP

INCRLOOP
ADD R1, R1, 1
BRnzp LOOPCONVERT


FINISH
HALT

CHKCASE .blkw 1

CHAR .fill 'p'

LOWER_A .fill 97
TOUPPER .fill -32
TOLOWER .fill 32
NULLTERM .fill '\0'

STRING .fill x4000

.end

.orig x4000
.stringz "APPLE"
.end