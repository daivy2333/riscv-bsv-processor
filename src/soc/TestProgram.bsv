// Auto-generated test program from hex file
package TestProgram;
import Types::*;
import Vector::*;

function Vector#(1024, Word) testProgram();
    Vector#(1024, Word) prog = replicate(0);

    prog[0] = 32'h00a00093;  // @ 0x80000000
    prog[1] = 32'h01400113;  // @ 0x80000004
    prog[2] = 32'h002081b3;  // @ 0x80000008
    prog[3] = 32'h00500513;  // @ 0x8000000c
    prog[4] = 32'hfff50513;  // @ 0x80000010
    prog[5] = 32'hfe051ee3;  // @ 0x80000014
    prog[6] = 32'h80001337;  // @ 0x80000018
    prog[7] = 32'h00100393;  // @ 0x8000001c
    prog[8] = 32'h00732023;  // @ 0x80000020
    prog[9] = 32'h0000006f;  // @ 0x80000024

    return prog;
endfunction
endpackage

// Generated 10 words
