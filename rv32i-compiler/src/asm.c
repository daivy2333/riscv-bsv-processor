#define _GNU_SOURCE
#include "asm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES  4096
#define MAX_LABELS 1024

struct AsmLine {
    int kind;       /* 0:skip  1:label  2:instruction */
    int addr;
    char text[256];
};

struct Label {
    char name[128];
    int addr;
};

/* ================================================================
 *  RV32I instruction encoding helpers (EXISTING — unchanged)
 * ================================================================ */

static uint32_t encode_itype(int32_t imm12, int rs1, int funct3, int rd, int opcode)
{
    return ((uint32_t)imm12 << 20) | ((rs1 & 0x1F) << 15) |
           ((funct3 & 0x7) << 12) | ((rd & 0x1F) << 7) | (opcode & 0x7F);
}

static uint32_t encode_stype(int32_t imm12, int rs2, int rs1, int funct3)
{
    uint32_t imm = (uint32_t)imm12;
    return (((imm >> 5) & 0x7F) << 25) | ((rs2 & 0x1F) << 20) |
           ((rs1 & 0x1F) << 15) | ((funct3 & 0x7) << 12) |
           ((imm & 0x1F) << 7) | 0x23;
}

static uint32_t encode_utype(int32_t imm20, int rd, int opcode)
{
    return (((uint32_t)imm20 & 0xFFFFF) << 12) |
           ((rd & 0x1F) << 7) | (opcode & 0x7F);
}

/* ================================================================
 *  NEW encoding helpers: R-type, B-type, J-type
 * ================================================================ */

static uint32_t encode_rtype(int funct7, int rs2, int rs1, int funct3, int rd, int opcode)
{
    return ((funct7 & 0x7F) << 25) | ((rs2 & 0x1F) << 20) |
           ((rs1 & 0x1F) << 15) | ((funct3 & 0x7) << 12) |
           ((rd & 0x1F) << 7) | (opcode & 0x7F);
}

/* B-type: [imm12|imm10:5][rs2][rs1][funct3][imm4:1|imm11][opcode=0x63] */
static uint32_t encode_btype(int32_t offset, int rs2, int rs1, int funct3)
{
    uint32_t imm = (uint32_t)(offset & 0x1FFE);  /* clear bit 0, ensure even */
    return ((imm >> 12) & 0x1)  << 31 |    /* imm[12]     */
           ((imm >>  5) & 0x3F) << 25 |    /* imm[10:5]   */
           ((rs2 & 0x1F)        << 20) |
           ((rs1 & 0x1F)        << 15) |
           ((funct3 & 0x7)      << 12) |
           ((imm >>  1) & 0xF)  <<  8 |    /* imm[4:1]    */
           ((imm >> 11) & 0x1)  <<  7 |    /* imm[11]     */
           0x63;
}

/* J-type: [imm20|imm10:1|imm11|imm19:12][rd][opcode=0x6F] */
static uint32_t encode_jtype(int32_t offset, int rd)
{
    uint32_t imm = (uint32_t)(offset & 0x1FFFFE);  /* clear bit 0 */
    return ((imm >> 20) & 0x1)   << 31 |    /* imm[20]     */
           ((imm >>  1) & 0x3FF) << 21 |    /* imm[10:1]   */
           ((imm >> 11) & 0x1)   << 20 |    /* imm[11]     */
           ((imm >> 12) & 0xFF)  << 12 |    /* imm[19:12]  */
           ((rd & 0x1F)          <<  7) |
           0x6F;
}

/* ================================================================
 *  Support helpers (EXISTING — unchanged)
 * ================================================================ */

static int reg_num(const char *s)
{
    if (s[0] == 'x' && isdigit(s[1]))
        return atoi(s + 1);
    if (s[0] == 'z' && s[1] == 'e' && s[2] == 'r' && s[3] == 'o' && !isalnum(s[4]))
        return 0;
    if (s[0] == 'r' && s[1] == 'a' && !isalnum(s[2])) return 1;
    if (s[0] == 's' && s[1] == 'p' && !isalnum(s[2])) return 2;
    if (s[0] == 'g' && s[1] == 'p' && !isalnum(s[2])) return 3;
    if (s[0] == 't' && s[1] == 'p' && !isalnum(s[2])) return 4;
    if (s[0] == 't' && s[1] >= '0' && s[1] <= '2') return 5 + (s[1] - '0');
    if (s[0] == 's' && s[1] == '0' && !isalnum(s[2])) return 8;
    if (s[0] == 's' && s[1] == '1' && !isalnum(s[2])) return 9;
    if (s[0] == 'a' && s[1] >= '0' && s[1] <= '7') return 10 + (s[1] - '0');
    if (s[0] == 's' && s[1] >= '2' && s[1] <= '9') return 18 + (s[1] - '2');
    if (s[0] == 's' && s[1] == '1' && s[2] == '0') return 26;
    if (s[0] == 's' && s[1] == '1' && s[2] == '1') return 27;
    if (s[0] == 't' && s[1] >= '3' && s[1] <= '6') return 28 + (s[1] - '3');
    return -1;
}

static int parse_int(const char *s)
{
    int sign = 1;
    if (*s == '-') { sign = -1; s++; }
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
        return sign * (int)strtol(s + 2, NULL, 16);
    return sign * atoi(s);
}

static const char *skip_space(const char *p)
{
    while (*p == ' ' || *p == '\t' || *p == '\r') p++;
    return p;
}

static void trim_newline(char *line)
{
    size_t len = strlen(line);
    while (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r'))
        line[--len] = '\0';
}

/* ================================================================
 *  NEW support helpers
 * ================================================================ */

static int is_numeric_str(const char *s)
{
    if (*s == '-') s++;
    if (*s >= '0' && *s <= '9') return 1;
    return 0;
}

static int lookup_label(const char *name,
                        const struct Label *labels, int label_count)
{
    for (int i = 0; i < label_count; i++)
        if (strcmp(labels[i].name, name) == 0)
            return labels[i].addr;
    return -1;
}

/* ================================================================
 *  assemble_line — MODIFIED: new signature, all existing + new insns
 * ================================================================ */

static int assemble_line(const char *line, int current_addr,
                         const struct Label *labels, int label_count,
                         uint32_t *word_out, const char **errmsg)
{
    const char *p = skip_space(line);
    if (*p == '\0' || *p == '#' || *p == ';')
        return -1;  /* empty/comment: skip */

    /* Check for label FIRST (before directive check).
     * A line like ".L1:" should be detected as a label, not skipped. */
    {
        const char *q = p;
        while (*q && *q != ':' && *q != ' ' && *q != '\t') q++;
        if (*q == ':') return -1;  /* label line — handled in pass 1 */
    }

    /* Directive: skip */
    if (*p == '.') return -1;

    /* === parse mnemonic === */
    char mnemonic[16];
    int mlen = 0;
    while (*p && *p != ' ' && *p != '\t' && mlen < 15)
        mnemonic[mlen++] = *p++;
    mnemonic[mlen] = '\0';
    p = skip_space(p);

    /* ================================================================
     *  Pseudo-instructions (expand to real instructions)
     * ================================================================ */

    if (strcmp(mnemonic, "mv") == 0) {       /* mv rd, rs  →  addi rd, rs, 0 */
        char rd_str[16], rs_str[16];
        if (sscanf(p, "%15[^,], %15s", rd_str, rs_str) != 2) {
            *errmsg = "mv: expected rd, rs"; return 0;
        }
        int rd = reg_num(rd_str), rs = reg_num(rs_str);
        if (rd < 0 || rs < 0) { *errmsg = "mv: unknown reg"; return 0; }
        *word_out = encode_itype(0, rs, 0, rd, 0x13);
        return 1;
    }
    if (strcmp(mnemonic, "neg") == 0) {      /* neg rd, rs  →  sub rd, x0, rs */
        char rd_str[16], rs_str[16];
        if (sscanf(p, "%15[^,], %15s", rd_str, rs_str) != 2) {
            *errmsg = "neg: expected rd, rs"; return 0;
        }
        int rd = reg_num(rd_str), rs = reg_num(rs_str);
        if (rd < 0 || rs < 0) { *errmsg = "neg: unknown reg"; return 0; }
        *word_out = encode_rtype(0x20, rs, 0, 0, rd, 0x33);
        return 1;
    }
    if (strcmp(mnemonic, "j") == 0) {        /* j label  →  jal x0, label */
        char offset_str[128];
        if (sscanf(p, "%127s", offset_str) != 1) {
            *errmsg = "j: expected label"; return 0;
        }
        int offset;
        if (is_numeric_str(offset_str)) {
            offset = parse_int(offset_str);
        } else {
            int target = lookup_label(offset_str, labels, label_count);
            if (target < 0) { *errmsg = "j: undefined label"; return 0; }
            offset = target - current_addr;
        }
        *word_out = encode_jtype(offset, 0);  /* rd = x0 */
        return 1;
    }
    if (strcmp(mnemonic, "beqz") == 0) {     /* beqz rs, label  →  beq rs, x0, label */
        char rs_str[16], offset_str[128];
        if (sscanf(p, "%15[^,], %127s", rs_str, offset_str) != 2) {
            *errmsg = "beqz: expected rs, label"; return 0;
        }
        int rs = reg_num(rs_str);
        if (rs < 0) { *errmsg = "beqz: unknown reg"; return 0; }
        int offset;
        if (is_numeric_str(offset_str)) {
            offset = parse_int(offset_str);
        } else {
            int target = lookup_label(offset_str, labels, label_count);
            if (target < 0) { *errmsg = "beqz: undefined label"; return 0; }
            offset = target - current_addr;
        }
        *word_out = encode_btype(offset, 0, rs, 0);  /* rs2=x0, funct3=0 (BEQ) */
        return 1;
    }
    if (strcmp(mnemonic, "bnez") == 0) {     /* bnez rs, label  →  bne rs, x0, label */
        char rs_str[16], offset_str[128];
        if (sscanf(p, "%15[^,], %127s", rs_str, offset_str) != 2) {
            *errmsg = "bnez: expected rs, label"; return 0;
        }
        int rs = reg_num(rs_str);
        if (rs < 0) { *errmsg = "bnez: unknown reg"; return 0; }
        int offset;
        if (is_numeric_str(offset_str)) {
            offset = parse_int(offset_str);
        } else {
            int target = lookup_label(offset_str, labels, label_count);
            if (target < 0) { *errmsg = "bnez: undefined label"; return 0; }
            offset = target - current_addr;
        }
        *word_out = encode_btype(offset, 0, rs, 1);  /* rs2=x0, funct3=1 (BNE) */
        return 1;
    }

    /* ================================================================
     *  EXISTING instructions (unchanged)
     * ================================================================ */

    if (strcmp(mnemonic, "addi") == 0) {
        char rd_str[16], rs1_str[16], imm_str[16];
        if (sscanf(p, "%15[^,], %15[^,], %15s", rd_str, rs1_str, imm_str) != 3) {
            *errmsg = "addi: expected rd, rs1, imm";
            return 0;
        }
        int rd = reg_num(rd_str), rs1 = reg_num(rs1_str);
        int imm = parse_int(imm_str);
        if (rd < 0 || rs1 < 0) { *errmsg = "addi: unknown reg"; return 0; }
        *word_out = encode_itype(imm, rs1, 0, rd, 0x13);
        return 1;
    }
    if (strcmp(mnemonic, "sw") == 0) {
        char rs2_str[16], offset_str[16], rs1_str[16];
        char lbracket[2];
        if (sscanf(p, "%15[^,], %15[^(]%1[(]%15[^)]", rs2_str, offset_str, lbracket, rs1_str) != 4) {
            *errmsg = "sw: expected rs2, offset(rs1)";
            return 0;
        }
        int rs2 = reg_num(rs2_str), rs1 = reg_num(rs1_str);
        int offset = parse_int(offset_str);
        if (rs2 < 0 || rs1 < 0) { *errmsg = "sw: unknown reg"; return 0; }
        *word_out = encode_stype(offset, rs2, rs1, 2);
        return 1;
    }
    if (strcmp(mnemonic, "lw") == 0) {
        char rd_str[16], offset_str[16], rs1_str[16];
        char lbracket[2];
        if (sscanf(p, "%15[^,], %15[^(]%1[(]%15[^)]", rd_str, offset_str, lbracket, rs1_str) != 4) {
            *errmsg = "lw: expected rd, offset(rs1)";
            return 0;
        }
        int rd = reg_num(rd_str), rs1 = reg_num(rs1_str);
        int offset = parse_int(offset_str);
        if (rd < 0 || rs1 < 0) { *errmsg = "lw: unknown reg"; return 0; }
        *word_out = encode_itype(offset, rs1, 2, rd, 0x03);
        return 1;
    }
    if (strcmp(mnemonic, "li") == 0) {
        char rd_str[16], imm_str[16];
        if (sscanf(p, "%15[^,], %15s", rd_str, imm_str) != 2) {
            *errmsg = "li: expected rd, imm";
            return 0;
        }
        int rd = reg_num(rd_str);
        int imm = parse_int(imm_str);
        if (rd < 0) { *errmsg = "li: unknown reg"; return 0; }
        *word_out = encode_itype(imm, 0, 0, rd, 0x13);
        return 1;
    }
    if (strcmp(mnemonic, "jalr") == 0) {
        char rd_str[16], rs1_str[16], imm_str[16];
        if (sscanf(p, "%15[^,], %15[^,], %15s", rd_str, rs1_str, imm_str) != 3) {
            *errmsg = "jalr: expected rd, rs1, imm";
            return 0;
        }
        int rd = reg_num(rd_str), rs1 = reg_num(rs1_str);
        int imm = parse_int(imm_str);
        if (rd < 0 || rs1 < 0) { *errmsg = "jalr: unknown reg"; return 0; }
        *word_out = encode_itype(imm, rs1, 0, rd, 0x67);
        return 1;
    }
    if (strcmp(mnemonic, "ret") == 0) {
        *word_out = encode_itype(0, 1, 0, 0, 0x67); /* jalr x0, x1, 0 */
        return 1;
    }
    if (strcmp(mnemonic, "lui") == 0) {
        char rd_str[16], imm_str[16];
        if (sscanf(p, "%15[^,], %15s", rd_str, imm_str) != 2) {
            *errmsg = "lui: expected rd, imm";
            return 0;
        }
        int rd = reg_num(rd_str);
        int imm = parse_int(imm_str);
        if (rd < 0) { *errmsg = "lui: unknown reg"; return 0; }
        *word_out = encode_utype(imm, rd, 0x37);
        return 1;
    }
    if (strcmp(mnemonic, "auipc") == 0) {
        char rd_str[16], imm_str[16];
        if (sscanf(p, "%15[^,], %15s", rd_str, imm_str) != 2) {
            *errmsg = "auipc: expected rd, imm";
            return 0;
        }
        int rd = reg_num(rd_str);
        int imm = parse_int(imm_str);
        if (rd < 0) { *errmsg = "auipc: unknown reg"; return 0; }
        *word_out = encode_utype(imm, rd, 0x17);
        return 1;
    }

    /* ================================================================
     *  NEW R-type instructions
     * ================================================================ */

    if (strcmp(mnemonic, "add") == 0) {
        char rd_str[16], rs1_str[16], rs2_str[16];
        if (sscanf(p, "%15[^,], %15[^,], %15s", rd_str, rs1_str, rs2_str) != 3) {
            *errmsg = "add: expected rd, rs1, rs2"; return 0;
        }
        int rd = reg_num(rd_str), rs1 = reg_num(rs1_str), rs2 = reg_num(rs2_str);
        if (rd < 0 || rs1 < 0 || rs2 < 0) { *errmsg = "add: unknown reg"; return 0; }
        *word_out = encode_rtype(0x00, rs2, rs1, 0, rd, 0x33);
        return 1;
    }
    if (strcmp(mnemonic, "sub") == 0) {
        char rd_str[16], rs1_str[16], rs2_str[16];
        if (sscanf(p, "%15[^,], %15[^,], %15s", rd_str, rs1_str, rs2_str) != 3) {
            *errmsg = "sub: expected rd, rs1, rs2"; return 0;
        }
        int rd = reg_num(rd_str), rs1 = reg_num(rs1_str), rs2 = reg_num(rs2_str);
        if (rd < 0 || rs1 < 0 || rs2 < 0) { *errmsg = "sub: unknown reg"; return 0; }
        *word_out = encode_rtype(0x20, rs2, rs1, 0, rd, 0x33);
        return 1;
    }
    if (strcmp(mnemonic, "sll") == 0) {
        char rd_str[16], rs1_str[16], rs2_str[16];
        if (sscanf(p, "%15[^,], %15[^,], %15s", rd_str, rs1_str, rs2_str) != 3) {
            *errmsg = "sll: expected rd, rs1, rs2"; return 0;
        }
        int rd = reg_num(rd_str), rs1 = reg_num(rs1_str), rs2 = reg_num(rs2_str);
        if (rd < 0 || rs1 < 0 || rs2 < 0) { *errmsg = "sll: unknown reg"; return 0; }
        *word_out = encode_rtype(0x00, rs2, rs1, 1, rd, 0x33);
        return 1;
    }
    if (strcmp(mnemonic, "srl") == 0) {
        char rd_str[16], rs1_str[16], rs2_str[16];
        if (sscanf(p, "%15[^,], %15[^,], %15s", rd_str, rs1_str, rs2_str) != 3) {
            *errmsg = "srl: expected rd, rs1, rs2"; return 0;
        }
        int rd = reg_num(rd_str), rs1 = reg_num(rs1_str), rs2 = reg_num(rs2_str);
        if (rd < 0 || rs1 < 0 || rs2 < 0) { *errmsg = "srl: unknown reg"; return 0; }
        *word_out = encode_rtype(0x00, rs2, rs1, 5, rd, 0x33);
        return 1;
    }
    if (strcmp(mnemonic, "sra") == 0) {
        char rd_str[16], rs1_str[16], rs2_str[16];
        if (sscanf(p, "%15[^,], %15[^,], %15s", rd_str, rs1_str, rs2_str) != 3) {
            *errmsg = "sra: expected rd, rs1, rs2"; return 0;
        }
        int rd = reg_num(rd_str), rs1 = reg_num(rs1_str), rs2 = reg_num(rs2_str);
        if (rd < 0 || rs1 < 0 || rs2 < 0) { *errmsg = "sra: unknown reg"; return 0; }
        *word_out = encode_rtype(0x20, rs2, rs1, 5, rd, 0x33);
        return 1;
    }
    if (strcmp(mnemonic, "and") == 0) {
        char rd_str[16], rs1_str[16], rs2_str[16];
        if (sscanf(p, "%15[^,], %15[^,], %15s", rd_str, rs1_str, rs2_str) != 3) {
            *errmsg = "and: expected rd, rs1, rs2"; return 0;
        }
        int rd = reg_num(rd_str), rs1 = reg_num(rs1_str), rs2 = reg_num(rs2_str);
        if (rd < 0 || rs1 < 0 || rs2 < 0) { *errmsg = "and: unknown reg"; return 0; }
        *word_out = encode_rtype(0x00, rs2, rs1, 7, rd, 0x33);
        return 1;
    }
    if (strcmp(mnemonic, "or") == 0) {
        char rd_str[16], rs1_str[16], rs2_str[16];
        if (sscanf(p, "%15[^,], %15[^,], %15s", rd_str, rs1_str, rs2_str) != 3) {
            *errmsg = "or: expected rd, rs1, rs2"; return 0;
        }
        int rd = reg_num(rd_str), rs1 = reg_num(rs1_str), rs2 = reg_num(rs2_str);
        if (rd < 0 || rs1 < 0 || rs2 < 0) { *errmsg = "or: unknown reg"; return 0; }
        *word_out = encode_rtype(0x00, rs2, rs1, 6, rd, 0x33);
        return 1;
    }
    if (strcmp(mnemonic, "xor") == 0) {
        char rd_str[16], rs1_str[16], rs2_str[16];
        if (sscanf(p, "%15[^,], %15[^,], %15s", rd_str, rs1_str, rs2_str) != 3) {
            *errmsg = "xor: expected rd, rs1, rs2"; return 0;
        }
        int rd = reg_num(rd_str), rs1 = reg_num(rs1_str), rs2 = reg_num(rs2_str);
        if (rd < 0 || rs1 < 0 || rs2 < 0) { *errmsg = "xor: unknown reg"; return 0; }
        *word_out = encode_rtype(0x00, rs2, rs1, 4, rd, 0x33);
        return 1;
    }
    if (strcmp(mnemonic, "slt") == 0) {
        char rd_str[16], rs1_str[16], rs2_str[16];
        if (sscanf(p, "%15[^,], %15[^,], %15s", rd_str, rs1_str, rs2_str) != 3) {
            *errmsg = "slt: expected rd, rs1, rs2"; return 0;
        }
        int rd = reg_num(rd_str), rs1 = reg_num(rs1_str), rs2 = reg_num(rs2_str);
        if (rd < 0 || rs1 < 0 || rs2 < 0) { *errmsg = "slt: unknown reg"; return 0; }
        *word_out = encode_rtype(0x00, rs2, rs1, 2, rd, 0x33);
        return 1;
    }
    if (strcmp(mnemonic, "sltu") == 0) {
        char rd_str[16], rs1_str[16], rs2_str[16];
        if (sscanf(p, "%15[^,], %15[^,], %15s", rd_str, rs1_str, rs2_str) != 3) {
            *errmsg = "sltu: expected rd, rs1, rs2"; return 0;
        }
        int rd = reg_num(rd_str), rs1 = reg_num(rs1_str), rs2 = reg_num(rs2_str);
        if (rd < 0 || rs1 < 0 || rs2 < 0) { *errmsg = "sltu: unknown reg"; return 0; }
        *word_out = encode_rtype(0x00, rs2, rs1, 3, rd, 0x33);
        return 1;
    }

    /* ================================================================
     *  NEW I-type shift instructions (shamt in imm, funct7 in upper imm)
     * ================================================================ */

    if (strcmp(mnemonic, "slli") == 0) {
        char rd_str[16], rs1_str[16], imm_str[16];
        if (sscanf(p, "%15[^,], %15[^,], %15s", rd_str, rs1_str, imm_str) != 3) {
            *errmsg = "slli: expected rd, rs1, shamt"; return 0;
        }
        int rd = reg_num(rd_str), rs1 = reg_num(rs1_str);
        int shamt = parse_int(imm_str);
        if (rd < 0 || rs1 < 0) { *errmsg = "slli: unknown reg"; return 0; }
        *word_out = encode_itype(shamt, rs1, 1, rd, 0x13);
        return 1;
    }
    if (strcmp(mnemonic, "srli") == 0) {
        char rd_str[16], rs1_str[16], imm_str[16];
        if (sscanf(p, "%15[^,], %15[^,], %15s", rd_str, rs1_str, imm_str) != 3) {
            *errmsg = "srli: expected rd, rs1, shamt"; return 0;
        }
        int rd = reg_num(rd_str), rs1 = reg_num(rs1_str);
        int shamt = parse_int(imm_str);
        if (rd < 0 || rs1 < 0) { *errmsg = "srli: unknown reg"; return 0; }
        *word_out = encode_itype(shamt, rs1, 5, rd, 0x13);
        return 1;
    }
    if (strcmp(mnemonic, "srai") == 0) {
        char rd_str[16], rs1_str[16], imm_str[16];
        if (sscanf(p, "%15[^,], %15[^,], %15s", rd_str, rs1_str, imm_str) != 3) {
            *errmsg = "srai: expected rd, rs1, shamt"; return 0;
        }
        int rd = reg_num(rd_str), rs1 = reg_num(rs1_str);
        int shamt = parse_int(imm_str);
        if (rd < 0 || rs1 < 0) { *errmsg = "srai: unknown reg"; return 0; }
        *word_out = encode_itype(shamt | 0x400, rs1, 5, rd, 0x13);
        return 1;
    }

    /* ================================================================
     *  NEW I-type ALU instructions
     * ================================================================ */

    if (strcmp(mnemonic, "andi") == 0) {
        char rd_str[16], rs1_str[16], imm_str[16];
        if (sscanf(p, "%15[^,], %15[^,], %15s", rd_str, rs1_str, imm_str) != 3) {
            *errmsg = "andi: expected rd, rs1, imm"; return 0;
        }
        int rd = reg_num(rd_str), rs1 = reg_num(rs1_str);
        int imm = parse_int(imm_str);
        if (rd < 0 || rs1 < 0) { *errmsg = "andi: unknown reg"; return 0; }
        *word_out = encode_itype(imm, rs1, 7, rd, 0x13);
        return 1;
    }
    if (strcmp(mnemonic, "ori") == 0) {
        char rd_str[16], rs1_str[16], imm_str[16];
        if (sscanf(p, "%15[^,], %15[^,], %15s", rd_str, rs1_str, imm_str) != 3) {
            *errmsg = "ori: expected rd, rs1, imm"; return 0;
        }
        int rd = reg_num(rd_str), rs1 = reg_num(rs1_str);
        int imm = parse_int(imm_str);
        if (rd < 0 || rs1 < 0) { *errmsg = "ori: unknown reg"; return 0; }
        *word_out = encode_itype(imm, rs1, 6, rd, 0x13);
        return 1;
    }
    if (strcmp(mnemonic, "xori") == 0) {
        char rd_str[16], rs1_str[16], imm_str[16];
        if (sscanf(p, "%15[^,], %15[^,], %15s", rd_str, rs1_str, imm_str) != 3) {
            *errmsg = "xori: expected rd, rs1, imm"; return 0;
        }
        int rd = reg_num(rd_str), rs1 = reg_num(rs1_str);
        int imm = parse_int(imm_str);
        if (rd < 0 || rs1 < 0) { *errmsg = "xori: unknown reg"; return 0; }
        *word_out = encode_itype(imm, rs1, 4, rd, 0x13);
        return 1;
    }
    if (strcmp(mnemonic, "slti") == 0) {
        char rd_str[16], rs1_str[16], imm_str[16];
        if (sscanf(p, "%15[^,], %15[^,], %15s", rd_str, rs1_str, imm_str) != 3) {
            *errmsg = "slti: expected rd, rs1, imm"; return 0;
        }
        int rd = reg_num(rd_str), rs1 = reg_num(rs1_str);
        int imm = parse_int(imm_str);
        if (rd < 0 || rs1 < 0) { *errmsg = "slti: unknown reg"; return 0; }
        *word_out = encode_itype(imm, rs1, 2, rd, 0x13);
        return 1;
    }
    if (strcmp(mnemonic, "sltiu") == 0) {
        char rd_str[16], rs1_str[16], imm_str[16];
        if (sscanf(p, "%15[^,], %15[^,], %15s", rd_str, rs1_str, imm_str) != 3) {
            *errmsg = "sltiu: expected rd, rs1, imm"; return 0;
        }
        int rd = reg_num(rd_str), rs1 = reg_num(rs1_str);
        int imm = parse_int(imm_str);
        if (rd < 0 || rs1 < 0) { *errmsg = "sltiu: unknown reg"; return 0; }
        *word_out = encode_itype(imm, rs1, 3, rd, 0x13);
        return 1;
    }

    /* ================================================================
     *  NEW B-type instructions
     * ================================================================ */

    if (strcmp(mnemonic, "beq") == 0) {
        char rs1_str[16], rs2_str[16], offset_str[128];
        if (sscanf(p, "%15[^,], %15[^,], %127s", rs1_str, rs2_str, offset_str) != 3) {
            *errmsg = "beq: expected rs1, rs2, offset"; return 0;
        }
        int rs1 = reg_num(rs1_str), rs2 = reg_num(rs2_str);
        if (rs1 < 0 || rs2 < 0) { *errmsg = "beq: unknown reg"; return 0; }
        int offset;
        if (is_numeric_str(offset_str)) {
            offset = parse_int(offset_str);
        } else {
            int target = lookup_label(offset_str, labels, label_count);
            if (target < 0) { *errmsg = "beq: undefined label"; return 0; }
            offset = target - current_addr;
        }
        *word_out = encode_btype(offset, rs2, rs1, 0);
        return 1;
    }
    if (strcmp(mnemonic, "bne") == 0) {
        char rs1_str[16], rs2_str[16], offset_str[128];
        if (sscanf(p, "%15[^,], %15[^,], %127s", rs1_str, rs2_str, offset_str) != 3) {
            *errmsg = "bne: expected rs1, rs2, offset"; return 0;
        }
        int rs1 = reg_num(rs1_str), rs2 = reg_num(rs2_str);
        if (rs1 < 0 || rs2 < 0) { *errmsg = "bne: unknown reg"; return 0; }
        int offset;
        if (is_numeric_str(offset_str)) {
            offset = parse_int(offset_str);
        } else {
            int target = lookup_label(offset_str, labels, label_count);
            if (target < 0) { *errmsg = "bne: undefined label"; return 0; }
            offset = target - current_addr;
        }
        *word_out = encode_btype(offset, rs2, rs1, 1);
        return 1;
    }
    if (strcmp(mnemonic, "blt") == 0) {
        char rs1_str[16], rs2_str[16], offset_str[128];
        if (sscanf(p, "%15[^,], %15[^,], %127s", rs1_str, rs2_str, offset_str) != 3) {
            *errmsg = "blt: expected rs1, rs2, offset"; return 0;
        }
        int rs1 = reg_num(rs1_str), rs2 = reg_num(rs2_str);
        if (rs1 < 0 || rs2 < 0) { *errmsg = "blt: unknown reg"; return 0; }
        int offset;
        if (is_numeric_str(offset_str)) {
            offset = parse_int(offset_str);
        } else {
            int target = lookup_label(offset_str, labels, label_count);
            if (target < 0) { *errmsg = "blt: undefined label"; return 0; }
            offset = target - current_addr;
        }
        *word_out = encode_btype(offset, rs2, rs1, 4);
        return 1;
    }
    if (strcmp(mnemonic, "bge") == 0) {
        char rs1_str[16], rs2_str[16], offset_str[128];
        if (sscanf(p, "%15[^,], %15[^,], %127s", rs1_str, rs2_str, offset_str) != 3) {
            *errmsg = "bge: expected rs1, rs2, offset"; return 0;
        }
        int rs1 = reg_num(rs1_str), rs2 = reg_num(rs2_str);
        if (rs1 < 0 || rs2 < 0) { *errmsg = "bge: unknown reg"; return 0; }
        int offset;
        if (is_numeric_str(offset_str)) {
            offset = parse_int(offset_str);
        } else {
            int target = lookup_label(offset_str, labels, label_count);
            if (target < 0) { *errmsg = "bge: undefined label"; return 0; }
            offset = target - current_addr;
        }
        *word_out = encode_btype(offset, rs2, rs1, 5);
        return 1;
    }
    if (strcmp(mnemonic, "bltu") == 0) {
        char rs1_str[16], rs2_str[16], offset_str[128];
        if (sscanf(p, "%15[^,], %15[^,], %127s", rs1_str, rs2_str, offset_str) != 3) {
            *errmsg = "bltu: expected rs1, rs2, offset"; return 0;
        }
        int rs1 = reg_num(rs1_str), rs2 = reg_num(rs2_str);
        if (rs1 < 0 || rs2 < 0) { *errmsg = "bltu: unknown reg"; return 0; }
        int offset;
        if (is_numeric_str(offset_str)) {
            offset = parse_int(offset_str);
        } else {
            int target = lookup_label(offset_str, labels, label_count);
            if (target < 0) { *errmsg = "bltu: undefined label"; return 0; }
            offset = target - current_addr;
        }
        *word_out = encode_btype(offset, rs2, rs1, 6);
        return 1;
    }
    if (strcmp(mnemonic, "bgeu") == 0) {
        char rs1_str[16], rs2_str[16], offset_str[128];
        if (sscanf(p, "%15[^,], %15[^,], %127s", rs1_str, rs2_str, offset_str) != 3) {
            *errmsg = "bgeu: expected rs1, rs2, offset"; return 0;
        }
        int rs1 = reg_num(rs1_str), rs2 = reg_num(rs2_str);
        if (rs1 < 0 || rs2 < 0) { *errmsg = "bgeu: unknown reg"; return 0; }
        int offset;
        if (is_numeric_str(offset_str)) {
            offset = parse_int(offset_str);
        } else {
            int target = lookup_label(offset_str, labels, label_count);
            if (target < 0) { *errmsg = "bgeu: undefined label"; return 0; }
            offset = target - current_addr;
        }
        *word_out = encode_btype(offset, rs2, rs1, 7);
        return 1;
    }

    /* ================================================================
     *  NEW J-type instruction
     * ================================================================ */

    if (strcmp(mnemonic, "jal") == 0) {
        char rd_str[16], offset_str[128];
        if (sscanf(p, "%15[^,], %127s", rd_str, offset_str) != 2) {
            *errmsg = "jal: expected rd, offset"; return 0;
        }
        int rd = reg_num(rd_str);
        if (rd < 0) { *errmsg = "jal: unknown reg"; return 0; }
        int offset;
        if (is_numeric_str(offset_str)) {
            offset = parse_int(offset_str);
        } else {
            int target = lookup_label(offset_str, labels, label_count);
            if (target < 0) { *errmsg = "jal: undefined label"; return 0; }
            offset = target - current_addr;
        }
        *word_out = encode_jtype(offset, rd);
        return 1;
    }

    *errmsg = "unknown mnemonic";
    return 0;
}

/* ================================================================
 *  asm_assemble — REWRITTEN for two-pass assembly
 * ================================================================ */

int asm_assemble(const char *input, uint32_t **out_words, size_t *out_count)
{
    char *src = strdup(input);
    if (!src) return 1;
    *out_words = NULL;
    *out_count = 0;

    struct AsmLine lines[MAX_LINES];
    struct Label   labels[MAX_LABELS];
    int line_count  = 0;
    int label_count = 0;
    int has_error   = 0;

    /* ================================================================
     *  PASS 1 — collect lines and labels
     * ================================================================ */

    int addr = 0;
    {
        char *saveptr;
        char *line_text = strtok_r(src, "\n", &saveptr);

        while (line_text && line_count < MAX_LINES) {
            char buf[512];
            strncpy(buf, line_text, sizeof(buf) - 1);
            buf[sizeof(buf) - 1] = '\0';
            trim_newline(buf);

            /* Trim trailing whitespace */
            char *end = buf + strlen(buf) - 1;
            while (end >= buf && (*end == ' ' || *end == '\t' || *end == '\r'))
                end--;
            *(end + 1) = '\0';

            /* Classification */
            {
                const char *p = skip_space(buf);
                if (p[0] == '\0' || p[0] == '#' || p[0] == ';') {
                    /* empty / comment → skip */
                    lines[line_count].kind = 0;
                    lines[line_count].addr = addr;
                    { size_t slen = strlen(buf); if (slen > 255) slen = 255; memcpy(lines[line_count].text, buf, slen); lines[line_count].text[slen] = '\0'; }
                    line_count++;
                } else if (end >= buf && *end == ':') {
                /* LABEL — ends with ':' (checked BEFORE directive prefix) */
                *end = '\0';  /* strip the colon */
                const char *label_name = skip_space(buf);  /* strip leading whitespace */
                if (label_count < MAX_LABELS) {
                    { size_t slen = strlen(label_name); if (slen > 127) slen = 127; memcpy(labels[label_count].name, label_name, slen); labels[label_count].name[slen] = '\0'; }
                    labels[label_count].addr = addr;
                    label_count++;
                }
                lines[line_count].kind = 1;
                lines[line_count].addr = addr;
                { size_t slen = strlen(buf); if (slen > 255) slen = 255; memcpy(lines[line_count].text, buf, slen); lines[line_count].text[slen] = '\0'; }
                line_count++;
                /* Labels don't advance addr */
            } else if (skip_space(buf)[0] == '.') {
                /* Directive → skip */
                lines[line_count].kind = 0;
                lines[line_count].addr = addr;
                { size_t slen = strlen(buf); if (slen > 255) slen = 255; memcpy(lines[line_count].text, buf, slen); lines[line_count].text[slen] = '\0'; }
                line_count++;
            } else {
                /* Instruction */
                lines[line_count].kind = 2;
                lines[line_count].addr = addr;
                { size_t slen = strlen(buf); if (slen > 255) slen = 255; memcpy(lines[line_count].text, buf, slen); lines[line_count].text[slen] = '\0'; }
                line_count++;
                addr += 4;
             }
            }
 
             line_text = strtok_r(NULL, "\n", &saveptr);
        }
    }

    /* ================================================================
     *  PASS 2 — assemble with label resolution
     * ================================================================ */

    size_t cap = 256;
    uint32_t *words = malloc(cap * sizeof(uint32_t));
    size_t count = 0;
    const char *errmsg = NULL;

    addr = 0;  /* reset address counter for pass 2 */

    for (int i = 0; i < line_count; i++) {
        if (lines[i].kind == 0) continue;  /* skip */
        if (lines[i].kind == 1) continue;  /* label */

        /* kind == 2: instruction */
        uint32_t w;
        int rc = assemble_line(lines[i].text, addr,
                               labels, label_count,
                               &w, &errmsg);
        if (rc == 1) {
            if (count >= cap) {
                cap *= 2;
                words = realloc(words, cap * sizeof(uint32_t));
            }
            words[count++] = w;
            addr += 4;
        } else if (rc == 0) {
            fprintf(stderr, "asm error at addr 0x%x: %s\n  %s\n",
                    addr, errmsg, lines[i].text);
            has_error = 1;
        }
        /* rc == -1: shouldn't happen in pass 2, but skip silently */
    }

    free(src);

    if (has_error) {
        free(words);
        return 1;
    }

    *out_words  = words;
    *out_count  = count;
    return 0;
}

/* ================================================================
 *  asm_free_words (EXISTING — unchanged)
 * ================================================================ */

void asm_free_words(uint32_t *words)
{
    free(words);
}
