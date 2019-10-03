;;=============================================================
;;CS 2110 - Fall 2019
;;Homework 6 - Bubble Sort
;;=============================================================
;;Name:
;;=============================================================

.orig x3000

;;PUT YOUR CODE HERE
LD R1, LENGTH
LD R4, ARRAY

ADD R1, R1, -1

LOOP
AND R0, R0, 0

INNER
NOT R3, R0
ADD R3, R3, 1
ADD R3, R1, R3 ;; y - x
BRp SWAPCHECKER
BRnzp CONTLOOP

SWAPCHECKER
AND R5, R5, 0
AND R7, R7, 0
ADD R5, R4, R0 ;; address of array[x]
ADD R7, R5, 1 ;; address of array[x + 1]
LDR R2, R5, 0 ;; R2 = array[x]
LDR R3, R7, 0 ;; R3 = array[x + 1]

NOT R6, R3
ADD R6, R6, 1 ;; R6 = -array[x + 1] || -R3
ADD R6, R6, R2 ;; R6 = array[x] - array[x + 1]

BRp SWAP ;; if (array[x] - array[x + 1] > 0)
BRnzp CONTINNER

SWAP
STR R2, R7, 0 ;; array[x + 1] = R2
STR R3, R5, 0 ;; array[x] = R3
BRnzp CONTINNER

CONTINNER
ADD R0, R0, 1 ;; x++
BRnzp INNER

CONTLOOP
ADD R1, R1, -1
BRp LOOP

HALT

ARRAY .fill x4000
LENGTH .fill 7
.end

.orig x4000
.fill 4
.fill 9
.fill 0
.fill 2
.fill 9
.fill 3
.fill 10
.end
