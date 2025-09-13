// convert.c
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

static void reverse_str(char *s) {
    size_t i = 0, j = strlen(s);
    if (j == 0) return;
    j--;
    while (i < j) {
        char t = s[i]; s[i] = s[j]; s[j] = t;
        i++; j--;
    }
}

static char digit_of(int v) {
    return (v < 10) ? ('0' + v) : ('A' + (v - 10));
}

void div_convert(uint32_t n, int base, char *out) {
    // Handle invalid bases defensively
    if (base < 2 || base > 16 || out == NULL) return;

    if (n == 0) {
        out[0] = '0'; out[1] = '\0';
        return;
    }

    char tmp[65];
    int pos = 0;
    while (n > 0) {
        int r = (int)(n % (uint32_t)base);
        tmp[pos++] = digit_of(r);
        n /= (uint32_t)base;
    }
    tmp[pos] = '\0';
    // reverse into out
    for (int i = 0; i < pos; i++) out[i] = tmp[pos - 1 - i];
    out[pos] = '\0';
}

void sub_convert(uint32_t n, int base, char *out) {
    if (base < 2 || base > 16 || out == NULL) return;

    if (n == 0) {
        out[0] = '0'; out[1] = '\0';
        return;
    }

    // Find highest power of base <= n
    uint32_t power = 1;
    while (1) {
        uint32_t next = power * (uint32_t)base;
        if (next == 0 || next > n) break; // overflow or exceeded n
        power = next;
    }

    // Build digits from highest power to lowest
    char buf[65]; int pos = 0;
    while (power > 0) {
        uint32_t digit = n / power;         // how many times power fits
        buf[pos++] = digit_of((int)digit);   // uppercase for hex
        n -= digit * power;                  // subtract that many
        power /= (uint32_t)base;             // go to next lower power
    }
    // Trim leading zeros that can appear when power overflow guard was conservative
    int start = 0;
    while (start + 1 < pos && buf[start] == '0') start++;
    int outlen = pos - start;
    for (int i = 0; i < outlen; i++) out[i] = buf[start + i];
    out[outlen] = '\0';
}

static void to_base(uint32_t n, int base, char *out) {
    // helper used by print_tables (division method, uppercase)
    div_convert(n, base, out);
}

void print_tables(uint32_t n) {
    char bin[65], oct[24], hex[17];

    // Original
    to_base(n, 2, bin);
    to_base(n, 8, oct);
    to_base(n, 16, hex);
    printf("Original: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, n, hex);

    // Left Shift by 3  (uint32_t semantics)
    uint32_t shifted = (uint32_t)(n << 3);
    to_base(shifted, 2, bin);
    to_base(shifted, 8, oct);
    to_base(shifted, 16, hex);
    printf("Left Shift by 3: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, shifted, hex);

    // AND with 0xFF
    uint32_t masked = n & 0xFFu;
    to_base(masked, 2, bin);
    to_base(masked, 8, oct);
    to_base(masked, 16, hex);
    printf("AND with 0xFF: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, masked, hex);
}