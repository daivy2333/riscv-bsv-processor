int swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return tmp;
}

int main() {
    int x = 1;
    int y = 2;
    swap(&x, &y);
    return x;
}