#include "ft_ssl.h"

static base16_digit_t digit_to_base16(const uint8_t c)
{
    if (c <= 9)
        return '0' + c;
    return 'A' + (c - 10);
}

static uint8_t base16_to_digit(const base16_digit_t c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    return (c - 'A') + 10;
}

base16_t dec_to_base16(const uint64_t a)
{
    base16_digit_t base16[BASE16_N_DIGITS + 1];

    for (size_t i = 0; i < BASE16_N_DIGITS; i++)
        base16[i] = digit_to_base16((a >> (64 - (i + 1) * 4)) & 0b1111);
    base16[BASE16_N_DIGITS] = '\0';
    return ft_strdup(base16);
}

uint64_t base16_to_dec(const base16_t base16)
{
    uint64_t a;

    a = 0x0;
    for (size_t i = 0; i < BASE16_N_DIGITS; i++)
        a = (a << 4) + base16_to_digit(base16[i]);
    return a;
}
