#include "ft_ssl.h"

static uint128_t sub128_64(const uint128_t a, const uint128_t b)
{
    bool      borrow;
    uint128_t difference;

    difference.low  = a.low - b.low;
    borrow          = a.low < b.low;
    difference.high = a.high - b.high - borrow;
    return difference;
}

uint64_t mod128(const uint128_t a, const uint64_t mod)
{
    __uint128_t remainder;

    remainder = (a.high << 64) | a.low;
    return remainder % mod;
}

uint128_t prod128(uint64_t a, uint64_t b)
{
    uint64_t  u1;
    uint64_t  v1;
    uint64_t  t;
    uint64_t  w3;
    uint64_t  w1;
    uint64_t  k;
    uint128_t product;

    u1 = a & 0xffffffff;
    v1 = b & 0xffffffff;
    t  = u1 * v1;
    w3 = t & 0xffffffff;
    k  = t >> 32;
    a >>= 32;
    t  = a * v1 + k;
    k  = t & 0xffffffff;
    w1 = t >> 32;
    b >>= 32;
    t            = u1 * b + k;
    k            = t >> 32;
    product.high = a * b + w1 + k;
    product.low  = (t << 32) + w3;
    return product;
}
