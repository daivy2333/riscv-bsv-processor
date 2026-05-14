struct Node {
    int value;
    struct Node* next;
};

struct Node g_n;

int main() {
    g_n.value = 42;
    struct Node* p = &g_n;
    return p->value;
}