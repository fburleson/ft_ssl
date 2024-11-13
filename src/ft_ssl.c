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
    byte_array_t           formatted;
    encrypted_byte_array_t rev_format;
    byte_array_t           decrypted;

    priv_key   = gen_priv_key(DEFAULT_PUB_EXP);
    mod        = priv_key.q * priv_key.p;
    fd         = open(".gitignore", O_RDONLY);
    bytes      = encode(fd);
    encrypted  = encrypt_bytes(&bytes, priv_key.pub_exp, mod);
    formatted  = format_encrypted_bytes(&encrypted);
    rev_format = format_bytes(&formatted);
    decrypted  = decrypt_bytes(&rev_format, priv_key.priv_exp, mod);
    for (size_t i = 0; i < bytes.size; i++)
        printf("%c", bytes.data[i]);
    printf("\n----- ENCRYPTED -----\n");
    for (size_t i = 0; i < formatted.size; i++)
        printf("%c", formatted.data[i]);
    printf("\n----- DECRYPTED -----\n");
    for (size_t i = 0; i < decrypted.size; i++)
        printf("%c", decrypted.data[i]);
    printf("\n----- PRIVATE KEY -----\n");
    printf("%lu\n", priv_key.priv_exp);
}

// int main(void)
// {
//     base64_t base64;
//     uint64_t base10;
//
//     base64 = dec_to_base64(1234567);
//     base10 = base64_to_dec(base64);
//     printf("%s\n", base64);
//     printf("%lu\n", base10);
// }

// int main(void)
// {
// }
