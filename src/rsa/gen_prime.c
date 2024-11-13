#include "ft_ssl.h"

static uint64_t solve_exp_factor(const uint64_t n)
{
    uint64_t exp;
    uint64_t factor;
    uint64_t a;
    uint64_t temp_pow;
    uint64_t result;

    a   = n - 1;
    exp = 1;
    while (true)
    {
        temp_pow = powl(2, exp);
        result   = a / temp_pow;
        if (temp_pow * result != a)
        {
            exp--;
            factor = a / powl(2, exp);
            break;
        }
        exp++;
    }
    return factor;
}

/*
 * miller rabin is a composite test
 * returns true if a is composite
 * returns false if a is probably prime (75% chance)
 */
static bool miller_rabin(const uint64_t n, const uint64_t witness)
{
    uint64_t m;
    uint64_t b;

    // 0, 1, 2 and 3 are not composite
    if (n <= 3)
        return false;
    if (n % 2 == 0)
        return true;
    m = solve_exp_factor(n);
    b = (uint64_t)powl(witness, m) % n;
    if (b == 1 || b == n - 1)
        return false;
    while (m != n - 1)
    {
        b = b * b % n;
        m *= 2;
        if (b == 1)
            return true;
        if (b == n - 1)
            return false;
    }
    return true;
}

static bool is_prime(const uint64_t a, const double p)
{
    double   err_probability;
    uint64_t witness;

    err_probability = 1;
    witness         = 2;
    do
    {
        if (miller_rabin(a, witness))
            return false;
        else
            err_probability *= MILLER_RABIN_ERR_PROB;
        witness++;
    } while (1 - err_probability < p && witness < a - 1);
    return true;
}

uint64_t gen_prime(void)
{
    int      random_dev;
    uint64_t n;

    random_dev = get_random_dev();
    n          = rand_range_ui64(random_dev, MIN_PRIME, MAX_PRIME);
    while (!is_prime(n, PRIME_NUM_PROBABILITY))
        n = rand_range_ui64(random_dev, MIN_PRIME, MAX_PRIME);
    close(random_dev);
    return n;
}
