#ifndef LINKER_H
#define LINKER_H

#include <stdint.h>
#include <stddef.h>

int linker_link(const char *user_asm_file, const char *crt0_asm_file,
                const char *lib_asm_file, const char *out_hex);

int linker_link_multi(const char *asm_files[], int num_files,
                      const char *crt0_asm_file,
                      const char *lib_asm_file, const char *out_hex);

#endif
