#include "ft_ssl.h"

static uint64_t mod_exp(const uint64_t a, const rsa_exp_t exp, const uint64_t mod)
{
    uint64_t exponent;
    uint64_t base;
    uint64_t result;

    result   = 1;
    exponent = exp;
    base     = a % mod;
    if (a == 0)
        return 0;
    while (exponent > 0)
    {
        if (exponent & 1)
            result = (result * base) % mod;
        exponent = exponent >> 1;
        base     = (base * base) % mod;
    }
    return result % mod;
}

uint64_t encrypt_byte(const byte_t m, const rsa_exp_t pub_exp, const uint64_t mod)
{
    uint64_t c;

    c = mod_exp(m, pub_exp, mod);
    return c;
}

byte_t decrypt_byte(const uint64_t c, const rsa_exp_t priv_exp, const uint64_t mod)
{
    byte_t m;

    m = mod_exp(c, priv_exp, mod);
    return m;
}
