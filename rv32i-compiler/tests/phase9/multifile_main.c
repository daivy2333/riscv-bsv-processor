/* main.c - multi-file compilation test */
#include "multifile_helper.h"

int main() {
    int result = add(7, 8);
    return result;  /* should return 15 */
}