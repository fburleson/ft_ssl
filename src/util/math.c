#include "ft_ssl.h"

uint64_t totient(const uint64_t p, const uint64_t q)
{
    return (p - 1) * (q - 1);
}

uint64_t key_mod(const uint64_t p, const uint64_t q)
{
    return p * q;
}

uint64_t ft_max(const uint64_t a, const uint64_t b)
{
    if (a > b)
        return a;
    return b;
}

__uint128_t mod_prod(const uint64_t a, const uint64_t b, const uint64_t mod)
{
    __uint128_t product;

    product = (a % mod) * (b % mod);
    return product % mod;
}

__uint128_t mod_pow(uint64_t a, uint64_t exp, const uint64_t mod)
{
    __uint128_t result;

    result = 1;
    a %= mod;
    if (a == 0)
        return 0;
    while (exp > 0)
    {
        if (exp & 0b1)
            result = mod_prod(result, a, mod);
        a   = mod_prod(a, a, mod);
        exp = exp >> 0b1;
    }
    return result;
}

