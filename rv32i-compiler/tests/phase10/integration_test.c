/* Phase 10 integration test: volatile + const + void + typedef + static */

struct Point {
    int x;
    int y;
};

typedef struct Point Pt;

static Pt global_pt;
volatile int state = 0;
const int VERSION = 10;

void init_pt(Pt *p, int x, int y) {
    p->x = x;
    p->y = y;
}

int get_version(void) {
    return VERSION;
}

int main(void) {
    Pt *p = &global_pt;
    init_pt(p, 5, 15);
    state = 1;
    int sum = p->x + p->y;
    int ver = get_version();
    return sum + ver + state;  /* 5+15+10+1 = 31 */
}