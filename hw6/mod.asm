;;=============================================================
;;CS 2110 - Fall 2019
;;Homework 6 - Modulus
;;=============================================================
;;Name: Omar Shaikh
;;=============================================================

.orig x3000

LD R0, A    ;;YOUR CODE GOES HERE
LD R1, B
NOT R1, R1
ADD	R1,	R1,	1 ;; -B

LOOP
ADD R0, R0, R1 ;; A = A - B
BRzp LOOP

ST	R0,	ANSWER

A   .fill x703A
B   .fill x00FE

ANSWER .blkw 1

.end