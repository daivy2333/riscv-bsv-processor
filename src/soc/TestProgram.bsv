// Auto-generated test program from hex file
package TestProgram;
import Types::*;
import Vector::*;

function Vector#(1024, Word) testProgram();
    Vector#(1024, Word) prog = replicate(0);

    prog[0] = 32'h06400293;  // @ 0x80000000
    prog[1] = 32'hfce28313;  // @ 0x80000004
    prog[2] = 32'h03200393;  // @ 0x80000008
    prog[3] = 32'h02731e63;  // @ 0x8000000c
    prog[4] = 32'h00000293;  // @ 0x80000010
    prog[5] = 32'h00028313;  // @ 0x80000014
    prog[6] = 32'h02031863;  // @ 0x80000018
    prog[7] = 32'h7ff28313;  // @ 0x8000001c
    prog[8] = 32'h7ff00393;  // @ 0x80000020
    prog[9] = 32'h02731263;  // @ 0x80000024
    prog[10] = 32'h80028313;  // @ 0x80000028
    prog[11] = 32'h80000393;  // @ 0x8000002c
    prog[12] = 32'h00731c63;  // @ 0x80000030
    prog[13] = 32'h800002b7;  // @ 0x80000034
    prog[14] = 32'hfff28293;  // @ 0x80000038
    prog[15] = 32'h00128313;  // @ 0x8000003c
    prog[16] = 32'h800003b7;  // @ 0x80000040
    prog[17] = 32'h00731263;  // @ 0x80000044
    prog[18] = 32'h0000006f;  // @ 0x80000048

    return prog;
endfunction
endpackage

// Generated 19 words
