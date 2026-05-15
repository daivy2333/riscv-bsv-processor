/* void parameter test - func(void) syntax */

int bar(void) {
    return 15;
}

void baz(void) {
    return;
}

int main(void) {
    int x = bar();
    baz();
    return x;
}