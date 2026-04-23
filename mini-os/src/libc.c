/* Mini-OS libc implementation */

#include <stdint.h>
#include <stddef.h>

void *memset(void *s, int c, size_t n)
{
    unsigned char *p = (unsigned char *)s;
    while (n--) {
        *p++ = (unsigned char)c;
    }
    return s;
}

void *memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}

uint32_t __mulsi3(uint32_t a, uint32_t b)
{
    uint32_t result = 0;
    while (b) {
        if (b & 1)
            result += a;
        a <<= 1;
        b >>= 1;
    }
    return result;
}

uint32_t __divsi3(uint32_t a, uint32_t b)
{
    if (b == 0) return 0;
    uint32_t result = 0;
    uint32_t shift = 0;
    while (b <= a && (b << 1) <= a) {
        b <<= 1;
        shift++;
    }
    while (shift >= 0) {
        if (a >= b) {
            a -= b;
            result |= (1 << shift);
        }
        b >>= 1;
        shift--;
    }
    return result;
}

uint32_t __umodsi3(uint32_t a, uint32_t b)
{
    return a - __divsi3(a, b) * b;
}