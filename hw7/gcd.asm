;;=======================================
;; CS 2110 - Fall 2019
;; Homework 7
;;=======================================
;; Name:
;;=======================================

;; In this file, you must implement the 'gcd' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff:
;; don't run this directly by pressing 'RUN' in complx, since there is nothing
;; put at address x3000. Instead, load it and use 'Debug' -> 'Simulate Subroutine
;; Call' and choose the 'gcd' label.


.orig x3000

halt

gcd
;; Arguments of GCD: integer n, integer m
;;
;; Psuedocode:
;; GCD(n, m):
;;     if n < m:
;;         return GCD(m,n)
;;     if n > m:
;;         return GCD(n - m, m)
;;     else:
;;         return n

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
        LDR R0,R5,#4 ; R0 <- a
        LDR R1,R5,#5 ; R0 <- b

        NOT R2, R1
        ADD R2, R2, #1
        ADD R2, R0, R2 ; a - b = R2

        BRz DONEgcd ; if a - b == 0, return n
        BRn SWAPgcd
        BRp SUBgcd

        SWAPgcd
            STR R0,R6,#-1 ; Push a on the stack -> on second
            STR R1,R6,#-2 ; Push b on the stack -> on first
            ADD R6,R6,#-2
            JSR gcd
            LDR R1,R6,#0
            ADD R6,R6,#3
            BR DONEgcd

        SUBgcd
            STR R2,R6,#-1 ; Push a - b on the stack (order of args yay)
            STR R1,R6,#-2 ; Push m on the stack
            ADD R6,R6,#-2
            JSR gcd
            LDR R1,R6,#0
            ADD R6,R6,#3
            BR DONEgcd

        DONEgcd
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

; Needed by Simulate Subroutine Call in complx
STACK .fill xF000
.end
