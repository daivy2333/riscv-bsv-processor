#include "full_helper.h"

extern int g_external;

int main() {
    int a = get_value();
    int b = g_external;
    return a + b + 25;
}
