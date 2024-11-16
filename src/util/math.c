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
