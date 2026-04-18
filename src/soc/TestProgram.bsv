// Auto-generated test program from hex file
package TestProgram;
import Types::*;
import Vector::*;

function Vector#(1024, Word) testProgram();
    Vector#(1024, Word) prog = replicate(0);

    prog[0] = 32'hf1402573;  // @ 0x80000000
    prog[1] = 32'h301025f3;  // @ 0x80000004
    prog[2] = 32'h30002673;  // @ 0x80000008
    prog[3] = 32'h000026b7;  // @ 0x8000000c
    prog[4] = 32'h88868693;  // @ 0x80000010
    prog[5] = 32'h30069073;  // @ 0x80000014
    prog[6] = 32'h30002773;  // @ 0x80000018
    prog[7] = 32'h123452b7;  // @ 0x8000001c
    prog[8] = 32'h67828293;  // @ 0x80000020
    prog[9] = 32'h30029373;  // @ 0x80000024
    prog[10] = 32'h10000293;  // @ 0x80000028
    prog[11] = 32'h3002a3f3;  // @ 0x8000002c
    prog[12] = 32'h10000293;  // @ 0x80000030
    prog[13] = 32'h3002be73;  // @ 0x80000034
    prog[14] = 32'h800012b7;  // @ 0x80000038
    prog[15] = 32'h00100e93;  // @ 0x8000003c
    prog[16] = 32'h01d2a023;  // @ 0x80000040
    prog[17] = 32'h0000006f;  // @ 0x80000044

    return prog;
endfunction
endpackage

// Generated 18 words
