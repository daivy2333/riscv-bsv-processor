/* extern keyword test: extern declaration for already-defined variable */
int g_val = 100;
extern int g_val;  /* declaration (should be ignored) */

int main() {
    return g_val;
}