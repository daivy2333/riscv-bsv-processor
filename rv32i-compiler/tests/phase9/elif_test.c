#define MODE 2

#ifdef UNDEFINED
int main() {
    return 0;
}
#elif MODE == 1
int main() {
    return 1;
}
#elif MODE == 2
int main() {
    return 2;
}
#else
int main() {
    return 3;
}
#endif