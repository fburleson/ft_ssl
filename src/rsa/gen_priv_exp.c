#include "ft_ssl.h"

static void xgcd(const uint64_t a, const uint64_t b, uint64_t *const x, uint64_t *const y)
{
    // The extended euclidean algorithm
    uint64_t x0;
    uint64_t y0;

    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return;
    }
    xgcd(b % a, a, &x0, &y0);
    *x = y0 - (b / a) * x0;
    *y = x0;
}

rsa_exp_t gen_priv_exp(const uint64_t pub_key, const uint64_t totient)
{
    rsa_exp_t priv_exp;
    uint64_t  _;

    xgcd(pub_key, totient, &priv_exp, &_);
    return priv_exp;
}
