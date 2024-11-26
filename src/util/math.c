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

uint64_t mod_prod(const uint64_t a, const uint64_t b, const uint64_t mod)
{
    return ((a % mod) * (b % mod)) % mod;
}

uint64_t mod_pow(uint64_t a, uint64_t exp, const uint64_t mod)
{
    uint64_t result;

    result = 1;
    a %= mod;
    if (a == 0)
        return 0;
    while (exp > 0)
    {
        if (exp & 0b1)
            result = (result * a) % mod;
        a   = (a * a) % mod;
        exp = exp >> 0b1;
    }
    return result;
}
