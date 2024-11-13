#include "ft_ssl.h"
#include <stdio.h>

// int main(void)
// {
//     byte_t     m;
//     uint64_t   encrypted;
//     byte_t     decrypted;
//     priv_key_t priv_key;
//     uint64_t   mod;
//
//     priv_key  = gen_priv_key(DEFAULT_PUB_EXP);
//     mod       = priv_key.q * priv_key.p;
//     m         = 10;
//     encrypted = encrypt_byte(m, priv_key.pub_exp, mod);
//     decrypted = decrypt_byte(encrypted, priv_key.priv_exp, mod);
//     printf("priv_exp:   %lu\n", priv_key.priv_exp);
//     printf("decrypted:  %u\n", decrypted);
// }

int main(void)
{
    priv_key_t             priv_key;
    uint64_t               mod;
    int                    fd;
    byte_array_t           bytes;
    encrypted_byte_array_t encrypted;
    byte_array_t           decrypted;

    priv_key  = gen_priv_key(DEFAULT_PUB_EXP);
    mod       = priv_key.q * priv_key.p;
    fd        = open(".gitignore", O_RDONLY);
    bytes     = encode(fd);
    encrypted = encrypt_bytes(&bytes, priv_key.pub_exp, mod);
    decrypted = decrypt_bytes(&encrypted, priv_key.priv_exp, mod);
    for (size_t i = 0; i < bytes.size; i++)
        printf("%c", bytes.data[i]);
    printf("\n----- ENCRYPTED -----\n");
    for (size_t i = 0; i < encrypted.size; i++)
        printf("%lu", encrypted.data[i]);
    printf("\n----- DECRYPTED -----\n");
    for (size_t i = 0; i < decrypted.size; i++)
        printf("%c", bytes.data[i]);
}
