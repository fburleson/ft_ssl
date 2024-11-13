#include "ft_ssl.h"

priv_key_t gen_priv_key(const rsa_exp_t pub_key)
{
    priv_key_t priv_key;

    priv_key.p        = gen_prime();
    priv_key.q        = gen_prime();
    priv_key.pub_exp  = pub_key;
    priv_key.priv_exp = gen_priv_exp(priv_key.pub_exp, totient(priv_key.q, priv_key.p));
    return priv_key;
}
