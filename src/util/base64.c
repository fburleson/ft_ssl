#include "ft_ssl.h"

static base64_digit_t digit_to_base64(const uint8_t c)
{
    if (c == 63)
        return '/';
    if (c == 62)
        return '+';
    if (c >= 52)
        return '0' + (c - 52);
    if (c >= 26)
        return 'a' + (c - 26);
    return 'A' + c;
}

static uint64_t base64_to_digit(const base64_digit_t c)
{
    if (c == '/')
        return 63;
    if (c == '+')
        return 62;
    if (c >= 'a')
        return 26 + (c - 'a');
    if (c >= 'A')
        return c - 'A';
    return 52 + (c - '0');
}

base64_t dec_to_base64(const uint64_t a)
{
    char base64[12];

    for (size_t i = 0; i < 10; i++)
        base64[i] = digit_to_base64((a >> (64 - (i + 1) * 6)) & 0b111111);
    base64[10] = digit_to_base64((a & 0b1111) << 2);
    base64[11] = '\0';
    return ft_strdup(base64);
}

uint64_t base64_to_dec(const base64_t base64)
{
    uint64_t a;

    a = 0b0;
    for (size_t i = 0; i < 10; i++)
        a = (a << 6) + base64_to_digit(base64[i]);
    a = ((a << 6) + base64_to_digit(base64[10])) >> 2;
    return a;
}
