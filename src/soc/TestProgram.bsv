// Auto-generated test program from hex file
package TestProgram;
import Types::*;
import Vector::*;

function Vector#(1024, Word) testProgram();
    Vector#(1024, Word) prog = replicate(0);

    prog[0] = 32'h00a00093;  // @ 0x80000000
    prog[1] = 32'h00300113;  // @ 0x80000004
    prog[2] = 32'hffb00193;  // @ 0x80000008
    prog[3] = 32'h40208233;  // @ 0x8000000c
    prog[4] = 32'h002092b3;  // @ 0x80000010
    prog[5] = 32'h08000313;  // @ 0x80000014
    prog[6] = 32'h002353b3;  // @ 0x80000018
    prog[7] = 32'h00200413;  // @ 0x8000001c
    prog[8] = 32'h4081d4b3;  // @ 0x80000020
    prog[9] = 32'h0011a533;  // @ 0x80000024
    prog[10] = 32'h0030a5b3;  // @ 0x80000028
    prog[11] = 32'h0020b633;  // @ 0x8000002c
    prog[12] = 32'h00f00693;  // @ 0x80000030
    prog[13] = 32'h00700713;  // @ 0x80000034
    prog[14] = 32'h00e6f7b3;  // @ 0x80000038
    prog[15] = 32'h00800813;  // @ 0x8000003c
    prog[16] = 32'h00300893;  // @ 0x80000040
    prog[17] = 32'h01186933;  // @ 0x80000044
    prog[18] = 32'h00c00993;  // @ 0x80000048
    prog[19] = 32'h00600a13;  // @ 0x8000004c
    prog[20] = 32'h0149cab3;  // @ 0x80000050
    prog[21] = 32'h0000efb7;  // @ 0x80000054
    prog[22] = 32'headf8f93;  // @ 0x80000058
    prog[23] = 32'h0000006f;  // @ 0x8000005c

    return prog;
endfunction
endpackage

// Generated 24 words
