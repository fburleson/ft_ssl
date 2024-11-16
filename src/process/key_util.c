#include "ft_ssl.h"

priv_key_t parse_priv_key(const char *content)
{
    priv_key_t priv_key;
    size_t     cidx;

    cidx         = ft_strlen(PRIV_KEY_BEGIN);
    priv_key.mod = base64_to_dec((const base64_t)(content + cidx));
    cidx += BASE64_N_DIGITS;
    priv_key.pub_exp = base64_to_dec((const base64_t)(content + cidx));
    cidx += BASE64_N_DIGITS;
    priv_key.q = base64_to_dec((const base64_t)(content + cidx));
    cidx += BASE64_N_DIGITS;
    priv_key.p = base64_to_dec((const base64_t)(content + cidx));
    cidx += BASE64_N_DIGITS;
    priv_key.priv_exp = base64_to_dec((const base64_t)(content + cidx));
    return priv_key;
}

pub_key_t parse_pub_key(const char *content)
{
    pub_key_t pub_key;
    size_t    cidx;

    cidx        = ft_strlen(PUB_KEY_BEGIN);
    pub_key.mod = base64_to_dec((const base64_t)(content + cidx));
    cidx += BASE64_N_DIGITS;
    pub_key.pub_exp = base64_to_dec((const base64_t)(content + cidx));
    return pub_key;
}

static void print_base64(const uint64_t a, const int fd)
{
    base64_t base64;

    base64 = dec_to_base64(a);
    write(fd, base64, BASE64_N_DIGITS);
    free(base64);
}

void print_priv_key(const priv_key_t *const priv_key, const int fd)
{
    write(fd, PRIV_KEY_BEGIN, ft_strlen(PRIV_KEY_BEGIN));
    print_base64(priv_key->mod, fd);
    print_base64(priv_key->pub_exp, fd);
    print_base64(priv_key->p, fd);
    print_base64(priv_key->q, fd);
    print_base64(priv_key->priv_exp, fd);
    write(fd, "\n", 1);
    write(fd, PRIV_KEY_END, ft_strlen(PRIV_KEY_END));
}

void print_pub_key(const pub_key_t *const pub_key, const int fd)
{
    write(fd, PUB_KEY_BEGIN, ft_strlen(PUB_KEY_BEGIN));
    print_base64(pub_key->mod, fd);
    print_base64(pub_key->pub_exp, fd);
    write(fd, "\n", 1);
    write(fd, PUB_KEY_END, ft_strlen(PUB_KEY_END));
}
