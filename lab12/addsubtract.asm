;;===============================
;; Name: 
;;===============================

.orig x3000

LD R0, ARRAY
LD R1, LENGTH

AND R2, R2, 0 ;; sum
AND R3, R3, 0 ;; status
AND R4, R4, 0 ;; index

LOOP
LDR R5, R0, 0 ;; load current element
ADD R3, R3, 0
BRz ADDNUMS

;; subtract nums
NOT R5, R5
ADD R5, R5, 1
ADD R2, R5, R2
ADD R3, R3, -1 ;; flip the status bit
BR INCRLOOP

ADDNUMS
ADD R2, R5, R2
ADD R3, R3, 1 ;; flip it back
BR INCRLOOP

INCRLOOP
ADD R0, R0, 1
ADD R1, R1, -1
BRnp LOOP

ST R2, RESULT
HALT


ARRAY .fill x6000
LENGTH .fill 7
RESULT .fill 0
.end

.orig x6000
.fill 3 ; +
.fill 5 ; -
.fill 1 ; +
.fill 4 ; -
.fill 6 ; +
.fill 8 ; -
.fill 12; +
.end
