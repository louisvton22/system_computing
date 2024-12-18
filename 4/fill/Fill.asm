// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

@WAIT
0;JMP

(WAIT)
@i
M=0
@KBD
D=M
@FILL
D;JNE
@CLEAR
D;JEQ
@WAIT
0;JMP

(FILL)
@i
M=0
(FILLLOOP)
@i
D=M
@8192
D=D-A
@WAIT
D;JEQ // do nothing if screen is entirely white
@SCREEN // set A to 16384
D=A // set D to 16384
@i // set A to i
D=D+M // D <- D + M[i]
A=D // A <- D
M=1 // M[D] = 1
@i
M=M+1
@KBD
D=M
@CLEAR
D;JEQ
@FILLLOOP
0;JMP

(CLEAR)
@i
M=0
(CLEARLOOP)
@i
D=M
@8192
D=D-A
@WAIT
D;JEQ // do nothing if screen is entirely white
@SCREEN // set A to 16384
D=A // set D to 16384
@i // set A to i
D=D+M // D <- D + M[i]
A=D // A <- D
M=0 // M[D] = 1
@i
M=M+1
@KBD
D=M
@FILL
D;JNE
@CLEARLOOP
0;JMP
