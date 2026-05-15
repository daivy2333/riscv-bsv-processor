/* void function with no explicit return */

void noop(void) {
    /* no return statement - implicit return at end */
}

int main(void) {
    noop();
    return 5;
}