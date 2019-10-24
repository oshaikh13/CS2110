; Go through linked list,
;    replace every node's data with its factorial, and add them to a total

;=======================================
;; CS 2110 - Fall 2019
;; Timed Lab 4
;;=======================================
;; Name: 
;;=======================================

;; Little reminder from your friendly neighborhood 2110 TA staff:
;; don't run this directly by pressing 'RUN' in complx, since there is nothing
;; put at address x3000. Instead, load it and use 'Debug' -> 'Simulate Subroutine
;; Call' and choose the 'sumFactorialsLL' label.

.orig x3000

halt

LISTHEAD .fill 0    ; Store the head of the list here.
LISTTAIL .fill 0    ; Store the tail of the list here.

sumFactorialsLL
;; Argument(s) of sumFactorialsLL: Node head (the address of the current node - head, to begin)

; Psuedocode:
; sumFactorialsLL(Node head) {
;    if head == null {return 0}
;    if LISTHEAD == 0 {LISTHEAD = head}
;    if head.next == null {LISTTAIL = head}
;    head.data = factorial(head.data)
;    sum = sumfactorials(head.next)
;    return sum + head.data
; }
;;BUILDUP
    ADD R6,R6,#-4 ; moves R6 down 4 to point (EFFC)
    ;Return Value will go in R6,#3 once we are done
    STR R7,R6,#2 ; save return address (EFFC)
    STR R5,R6,#1 ; save old FP (EFFD)
    ADD R5,R6,#0 ; establish FP (move FP to current stack pointer) (this is where first temp variable is - answer)
    ADD R6,R6,#-5 ; make space for saved registers (5 of them) and move stack pointer
    STR R0,R5,#-1 ; SAVE REGISTERS
    STR R1,R5,#-2 ;
    STR R2,R5,#-3 ;
    STR R3,R5,#-4 ;
    STR R4,R5,#-5 ;

;;SUBROUTINE CODE
    LDR R0,R5,#4 ; R0 <- head
    BRz FINISH

    LDR R1,R0, #0 ; <- next

    LD R4, LISTHEAD
    BRz STORE_LISTHEAD
    BR CONT

    STORE_LISTHEAD
    ST R0, LISTHEAD

    CONT
    ADD R1, R1, 0
    BRz STORE_LISTTAIL
    
    STORE_LISTTAIL
    ST R0, LISTTAIL
    BR CONTNEXT
    

    CONTNEXT
    LDR R2, R0, #1 ; <- data
    STR R2,R6,#-1 ; Push head.data on the stack
    ADD R6,R6,#-1
    JSR factorial
    LDR R3,R6,#0 ; <- the result
    ADD R6,R6,#2
    STR R3, R0, #1


    STR R1,R6,#-1 ; Push head.next on the stack
    ADD R6,R6,#-1
    JSR sumFactorialsLL
    LDR R3,R6,#0 ; <- the result
    ADD R6,R6,#2


    LDR R2, R0, #1 ; <- data
    ADD R3, R3, R2
    STR R3, R5, #3
    BR TEARDOWN

    FINISH
    STR R0, R5, #3
    BR TEARDOWN

;;TEARDOWN
    TEARDOWN
    LDR R4,R5,#-5 ; RESTORE SAVED REGISTERS
    LDR R3,R5,#-4 ;
    LDR R2,R5,#-3 ;
    LDR R1,R5,#-2 ;
    LDR R0,R5,#-1 ;
    ADD R6,R5,#0 ; move stack pointer back down
    LDR R5,R6,#1 ; Restore old FP
    LDR R7,R6,#2 ; Restore return address
    ADD R6,R6,#3 ; move stack pointer to RV (return value)
    RET




;; =====================================================================
;; YOUR CODE GOES ABOVE HERE
;; DO NOT CHANGE CODE BELOW THIS LINE

factorial
;; Subroutine to get the factorial of a number
;; Accepts one parameter, n, and returns n!
;; You will need to call this subroutine once
    .fill x1dbc
    .fill x7f82
    .fill x7b81
    .fill x1ba0
    .fill x1dbb
    .fill x717f
    .fill x737e
    .fill x757d
    .fill x777c
    .fill x797b
    .fill x6144
    .fill x040d
    .fill x123f
    .fill x1dbf
    .fill x7380
    .fill x4ff0
    .fill x6380
    .fill x1da2
    .fill x1dbe
    .fill x7380
    .fill x7181
    .fill x480f
    .fill x6180
    .fill x1da3
    .fill x0e01
    .fill x1021
    .fill x7143
    .fill x697b
    .fill x677c
    .fill x657d
    .fill x637e
    .fill x617f
    .fill x1d60
    .fill x6b81
    .fill x6f82
    .fill x1da3
    .fill xc1c0

mult
; Recursive MULT subroutine
; Accepts 2 parameters, n and m, and returns n*m
; You shouldn't need to use this directly
    .fill x1dbc
    .fill x7f82
    .fill x7b81
    .fill x1ba0
    .fill x1dbb
    .fill x717f
    .fill x737e
    .fill x757d
    .fill x777c
    .fill x797b
    .fill x6144
    .fill x6345
    .fill x56e0
    .fill x54a0
    .fill x5241
    .fill x0603
    .fill x927f
    .fill x1261
    .fill x16e1
    .fill x5241
    .fill x0c03
    .fill x1480
    .fill x127f
    .fill x0ffb
    .fill x16ff
    .fill x0a02
    .fill x94bf
    .fill x14a1
    .fill x7543
    .fill x697b
    .fill x677c
    .fill x657d
    .fill x637e
    .fill x617f
    .fill x1d60
    .fill x6b81
    .fill x6f82
    .fill x1da3
    .fill xc1c0

; Needed by Simulate Subroutine Call in complx
STACK .fill xF000
.end
