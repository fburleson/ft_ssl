#include "ft_ssl.h"
#include <stdio.h>

int main(void)
{
    byte_t     m;
    uint64_t   encrypted;
    byte_t     decrypted;
    priv_key_t priv_key;
    uint64_t   mod;

    priv_key  = gen_priv_key(DEFAULT_PUB_EXP);
    mod       = priv_key.q * priv_key.p;
    m         = 10;
    encrypted = encrypt_byte(m, priv_key.pub_exp, mod);
    decrypted = decrypt_byte(encrypted, priv_key.priv_exp, mod);
    printf("priv_exp:   %lu\n", priv_key.priv_exp);
    printf("decrypted:  %u\n", decrypted);
}
