struct Node {
    int value;
    struct Node* next;
};

struct Node g_n1;
struct Node g_n2;
struct Node g_n3;

int sum_list(struct Node* head) {
    int total = 0;
    struct Node* p = head;
    while (p != 0) {
        total = total + p->value;
        p = p->next;
    }
    return total;
}

int main() {
    g_n1.value = 10;
    g_n1.next = &g_n2;
    g_n2.value = 20;
    g_n2.next = &g_n3;
    g_n3.value = 30;
    g_n3.next = 0;
    return sum_list(&g_n1);
}