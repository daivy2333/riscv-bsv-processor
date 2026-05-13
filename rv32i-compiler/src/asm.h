#ifndef ASM_H
#define ASM_H

#include <stddef.h>
#include <stdint.h>

int asm_assemble(const char *input, uint32_t **out_words, size_t *out_count);
void asm_free_words(uint32_t *words);

#endif
