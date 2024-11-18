#include "ft_ssl.h"
#include <stdio.h>

static size_t skip_to_key(const char *content, const char *key_begin)
{
    size_t idx;

    idx = 0;
    while (content[idx] && !ft_strequals_delimiter(content + idx, key_begin, '\n'))
    {
        while (content[idx] && content[idx] != '\n')
            idx++;
        while (content[idx] == '\n')
            idx++;
    }
    return idx;
}

priv_key_t parse_priv_key(const char *content)
{
    priv_key_t priv_key;
    size_t     cidx;

    cidx = skip_to_key(content, PRIV_KEY_BEGIN);
    cidx += ft_strlen(PRIV_KEY_BEGIN);
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

    cidx = skip_to_key(content, PUB_KEY_BEGIN);
    cidx += ft_strlen(PUB_KEY_BEGIN);
    pub_key.mod = base64_to_dec((const base64_t)(content + cidx));
    cidx += BASE64_N_DIGITS;
    pub_key.pub_exp = base64_to_dec((const base64_t)(content + cidx));
    return pub_key;
}

static void print_base64(const uint64_t a, const int fd)
{
    base64_t base64;

    base64 = dec_to_base64(a);
    print_str_fd(base64, fd);
    free(base64);
}

void print_priv_key(const priv_key_t *const priv_key, const int fd)
{
    print_str_fd(PRIV_KEY_BEGIN, fd);
    print_base64(priv_key->mod, fd);
    print_base64(priv_key->pub_exp, fd);
    print_base64(priv_key->p, fd);
    print_base64(priv_key->q, fd);
    print_base64(priv_key->priv_exp, fd);
    print_str_fd("\n" PRIV_KEY_BEGIN, fd);
}

void print_pub_key(const pub_key_t *const pub_key, const int fd)
{
    print_str_fd(PUB_KEY_BEGIN, fd);
    print_base64(pub_key->mod, fd);
    print_base64(pub_key->pub_exp, fd);
    print_str_fd("\n" PUB_KEY_END, fd);
}

static void print_base16(const uint64_t a, const int fd)
{
    base16_t base16;

    base16 = dec_to_base16(a);
    print_str_fd("0x", fd);
    print_str_fd(base16, fd);
    free(base16);
}

static void print_key_component(const char *name, const uint64_t value, const int fd)
{
    print_str_fd(name, fd);
    print_str_fd(": ", fd);
    print_base16(value, fd);
    print_str_fd("\n", fd);
}

void print_priv_key_text(const priv_key_t *const priv_key, const int fd)
{
    print_str_fd("private key: (64 bit, 2 primes)\n", fd);
    print_key_component("mod", priv_key->mod, fd);
    print_key_component("public exponent", priv_key->pub_exp, fd);
    print_key_component("private exponent", priv_key->priv_exp, fd);
    print_key_component("prime1", priv_key->p, fd);
    print_key_component("prime2", priv_key->q, fd);
}

void print_pub_key_text(const pub_key_t *const pub_key, const int fd)
{
    print_str_fd("public key: (64 bit)\n", fd);
    print_key_component("mod", pub_key->mod, fd);
    print_key_component("public exponent", pub_key->pub_exp, fd);
}
