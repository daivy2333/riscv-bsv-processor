char *g_msg;

int strlen(char *s) {
    int n = 0;
    while (*s) {
        n = n + 1;
        s = s + 1;
    }
    return n;
}

int main() {
    g_msg = "world";
    return strlen(g_msg);
}