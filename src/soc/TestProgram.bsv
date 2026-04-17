// Auto-generated test program from hex file
package TestProgram;
import Types::*;
import Vector::*;

function Vector#(1024, Word) testProgram();
    Vector#(1024, Word) prog = replicate(0);

    prog[0] = 32'h00a00093;  // @ 0x80000000
    prog[1] = 32'h01400113;  // @ 0x80000004
    prog[2] = 32'h002081b3;  // @ 0x80000008
    prog[3] = 32'h00118233;  // @ 0x8000000c
    prog[4] = 32'h003202b3;  // @ 0x80000010
    prog[5] = 32'h00001337;  // @ 0x80000014
    prog[6] = 32'h00532023;  // @ 0x80000018
    prog[7] = 32'h00032383;  // @ 0x8000001c
    prog[8] = 32'h00138433;  // @ 0x80000020
    prog[9] = 32'h00500513;  // @ 0x80000024
    prog[10] = 32'hfff50513;  // @ 0x80000028
    prog[11] = 32'hfe051ee3;  // @ 0x8000002c
    prog[12] = 32'h00a00593;  // @ 0x80000030
    prog[13] = 32'h01400613;  // @ 0x80000034
    prog[14] = 32'h00c5c463;  // @ 0x80000038
    prog[15] = 32'h3e700693;  // @ 0x8000003c
    prog[16] = 32'h06400693;  // @ 0x80000040
    prog[17] = 32'h0080076f;  // @ 0x80000044
    prog[18] = 32'h3e700793;  // @ 0x80000048
    prog[19] = 32'h0c800793;  // @ 0x8000004c
    prog[20] = 32'h0000efb7;  // @ 0x80000050
    prog[21] = 32'headf8f93;  // @ 0x80000054
    prog[22] = 32'h0000006f;  // @ 0x80000058

    return prog;
endfunction
endpackage

// Generated 23 words
