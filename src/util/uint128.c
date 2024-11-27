#include "ft_ssl.h"

static uint128_t add128_64(const uint128_t a, const uint64_t b)
{
    unsigned int carry;
    uint128_t    sum;

    sum.low  = a.low + b;
    carry    = sum.low < b;
    sum.high = a.high + carry;
    return sum;
}

static uint128_t sub128_64(const uint128_t a, const uint64_t b)
{
    bool      borrow;
    uint128_t difference;

    difference.low  = a.low - b;
    borrow          = a.low < b;
    difference.high = a.high - borrow;
    return difference;
}

uint64_t mod128(const uint128_t a, const uint64_t mod)
{
    uint128_t remainder;

    remainder = a;
    while (remainder.high)
        remainder = sub128_64(remainder, mod);
    remainder.low %= mod;
    return remainder.low;
}

uint128_t prod128(uint64_t a, uint64_t b)
{
    uint128_t product;

    product.low  = 0;
    product.high = 0;
    while (b > 0)
    {
        if (b & 1)
            product = add128_64(product, a);
        a <<= 1;
        b >>= 1;
    }
    return product;
}
