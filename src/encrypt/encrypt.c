#include "ft_ssl.h"

encrypted_byte_t encrypt_byte(const byte_t m, const rsa_exp_t pub_exp, const uint64_t mod)
{
    uint64_t c;

    c = mod_pow(m, pub_exp, mod);
    return c;
}

byte_t decrypt_byte(const encrypted_byte_t c, const rsa_exp_t priv_exp, const uint64_t mod)
{
    byte_t m;

    m = mod_pow128(c, priv_exp, mod);
    return m;
}

byte_array_t encrypt_bytes(const byte_array_t *const bytes, const rsa_exp_t pub_exp, const uint64_t mod)
{
    byte_array_t encrypted;

    encrypted = init_byte_array(bytes->size * sizeof(encrypted_byte_t));
    for (size_t i = 0; i < bytes->size; i++)
        ((encrypted_byte_t *)encrypted.data)[i] = encrypt_byte(bytes->data[i], pub_exp, mod);
    return encrypted;
}

byte_array_t decrypt_bytes(const byte_array_t *const bytes, const rsa_exp_t priv_exp, const uint64_t mod)
{
    byte_array_t decrypted;

    decrypted = init_byte_array(bytes->size / sizeof(encrypted_byte_t));
    for (size_t i = 0; i < decrypted.size; i++)
        decrypted.data[i] = decrypt_byte(((encrypted_byte_t *)bytes->data)[i], priv_exp, mod);
    return decrypted;
}
