;;=============================================================
;;CS 2110 - Fall 2019
;;Homework 6 - Sum the Elements of a Linked List
;;=============================================================
;;Name:
;;=============================================================

.orig x3000

;; YOUR CODE GOES HERE
AND R0, R0, 0 ;; sum
LD R1, LL
LDR R2, R1, 0 ;; R2 = addr of start
LDR R3, R1, 1 ;; R3 = length

LOOP
LDR R5, R2, 1
ADD R0, R0, R5
LDR R2, R2, 0 ;; load address of next node 
ADD R3, R3, -1
BRz FINISH
BRnzp LOOP

FINISH
ST R0, ANSWER
HALT

LL .fill x6000
ANSWER .blkw 1
.end

.orig x4000
.fill x4008
.fill 5
.fill x400A
.fill 2
.fill x4002
.fill 9
.fill x0000 
.fill 3
.fill x4004
.fill 10
.fill x4006
.fill 7
.end

.orig x6000
.fill x4000
.fill 6
.end
