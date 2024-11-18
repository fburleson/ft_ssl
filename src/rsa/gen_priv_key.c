#include "ft_ssl.h"

static bool is_valid_priv_key(const priv_key_t *const priv_key)
{
    uint64_t phi_mod;

    if (priv_key->p == priv_key->q)
        return false;
    phi_mod = totient(priv_key->q, priv_key->p);
    return mod_prod(priv_key->pub_exp, priv_key->priv_exp, phi_mod) == 1;
}

static priv_key_t try_gen_priv_key(const rsa_exp_t pub_key)
{
    priv_key_t priv_key;

    priv_key.p        = gen_prime();
    priv_key.q        = gen_prime();
    priv_key.mod      = key_mod(priv_key.p, priv_key.q);
    priv_key.pub_exp  = pub_key;
    priv_key.priv_exp = gen_priv_exp(priv_key.pub_exp, totient(priv_key.q, priv_key.p));
    return priv_key;
}

priv_key_t gen_priv_key(const rsa_exp_t pub_key)
{
    priv_key_t priv_key;

    do
    {
        priv_key = try_gen_priv_key(pub_key);
    } while (!is_valid_priv_key(&priv_key));
    return priv_key;
}
