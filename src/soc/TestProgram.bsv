// Auto-generated test program from hex file
package TestProgram;
import Types::*;
import Vector::*;

function Vector#(1024, Word) testProgram();
    Vector#(1024, Word) prog = replicate(0);

    prog[0] = 32'h00000093;  // @ 0x80000000
    prog[1] = 32'h00018137;  // @ 0x80000004
    prog[2] = 32'h6a010113;  // @ 0x80000008
    prog[3] = 32'h00108093;  // @ 0x8000000c
    prog[4] = 32'h3ff0f193;  // @ 0x80000010
    prog[5] = 32'h00019863;  // @ 0x80000014
    prog[6] = 32'h10000237;  // @ 0x80000018
    prog[7] = 32'h04100293;  // @ 0x8000001c
    prog[8] = 32'h00522023;  // @ 0x80000020
    prog[9] = 32'hfe9ff06f;  // @ 0x80000024

    return prog;
endfunction
endpackage

// Generated 10 words
