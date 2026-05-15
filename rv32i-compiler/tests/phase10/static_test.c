/* static global variable test */

static int counter = 5;

int get_counter(void) {
    return counter;
}

void increment(void) {
    counter = counter + 1;
}

int main(void) {
    increment();
    increment();
    return get_counter();  /* should return 7 */
}