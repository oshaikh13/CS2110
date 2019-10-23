;=======================================
;; CS 2110 - Fall 2019
;; Homework 7
;;=======================================
;; Name:
;;=======================================

;; In this file, you must implement the 'multiplyArgs' subroutine.
;; You are given the 'MULT' subroutine; use this as you wish.

;; Little reminder from your friendly neighborhood 2110 TA staff:
;; don't run this directly by pressing 'RUN' in complx, since there is nothing
;; put at address x3000. Instead, load it and use 'Debug' -> 'Simulate Subroutine
;; Call' and choose the 'multiplyArgs' label.

.orig x3000

halt

multiplyArgs
;; Arguments of multiplyAgrs: int numOfArgs, int arg1, int arg2, ..., int argN
;;
;; Psuedocode:
;; total = 1
;; while (numOfArgsLeft > 0):
;;     total =  mult(total, nextArg)
;;
;; return total

    ;; BUILDUP
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

    ;; SUBROUTINE CODE

        AND R1, R1, 0
        ADD R1, R1, 1

        ADD R2, R5, #4 ;; address of first arg i.e. A in func(A, B)
        LDR R0, R2, #0 ;; numargsleft
        BRz FINISH
        
        ADD R2, R2, #1
        
        LOOPMULT
            LDR R3, R2, #0 ;; arg_x

            STR R1,R6,#-1 ; Push total on the stack
            STR R3,R6,#-2 ; Push arg_x on the stack
            ADD R6,R6,#-2 ; Update the stack pointer
            JSR MULT ; MULT(arg_x, total)
            LDR R1, R6, #0 ; R1 <- return value
            ADD R6, R6, #3 ; 3 = num_args + return

            ADD R2, R2, #1
            ADD R0, R0, #-1

            BRp LOOPMULT
            BR FINISH

        ; STR R1,R6,#-1 ; Push factorial(n-1) on the stack
        ; STR R0,R6,#-2 ; Push n on the stack
        ; ADD R6,R6,#-2 ; Update the stack pointer
        ; JSR MULT
        ; LDR R1, R6, #0 ; R1 <- return value
        ; ADD R6, R6, #3 

        FINISH
            STR R1,R5,#3 ; Store return value on the stack

    ;; TEARDOWN
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

RET

MULT
    ; Recursive MULT
    ;;BUILDUP
    BUILDUPmult
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
    SUBROUTINEmult
        ;; int a is the leftmost arg (R5 + 4)
        LDR R0,R5,#4 ; Load int a into R0
        LDR R1,R5,#5 ; Load int b into R1
        
        AND R3,R3,#0 ; Clear R3 for keeping track of positive or negative
        AND R2,R2,#0 ; Clear R2 and reserve it for VALUE (the thing you'll return)
        AND R1,R1,R1 ; Get condition code of int b
        BRzp MULTLOOPmult ; if b ≥ 0, continue as normal
        ; if b is negative, make it positive and set R3 = 1 (used later)
        NOT R1,R1
        ADD R1,R1,#1
        AND R3,R3,#0
        ADD R3,R3,#1

        MULTLOOPmult
        AND R1,R1,R1 ; Just to make sure we're looking at int b
        BRnz OUTOFMULTLOOPmult ; if b ≤ 0, break the loop
        ADD R2,R2,R0 ; Add a to VALUE
        ADD R1,R1,#-1 ; decrement b
        BR MULTLOOPmult

        OUTOFMULTLOOPmult
            ADD R3,R3,#-1 ; Subtract 1 from R3
            BRnp NEXTmult; if R3 != 1, then skip this step
            ; if R3 == 1 (b was negative earlier), make return value negative
            NOT R2,R2
            ADD R2,R2,#1
            NEXTmult
            STR R2,R5,#3 ; Store VALUE in the return value spot on stack (R5 + 3)


    ;;TEARDOWN
    TEARDOWNmult
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


; Needed by Simulate Subroutine Call in complx
STACK .fill xF000
.end
