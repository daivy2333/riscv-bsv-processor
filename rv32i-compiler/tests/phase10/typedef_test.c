/* typedef struct alias test */

struct Point {
    int x;
    int y;
};

typedef struct Point PointAlias;

PointAlias global_pt;

int main(void) {
    PointAlias *p = &global_pt;
    p->x = 10;
    p->y = 20;
    return p->x + p->y;
}