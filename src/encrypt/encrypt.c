#include "ft_ssl.h"

static uint64_t mod_exp(const uint64_t a, const rsa_exp_t exp, const uint64_t mod)
{
    uint64_t exponent;
    uint64_t base;
    uint64_t result;

    result   = 1;
    exponent = exp;
    base     = a % mod;
    if (a == 0)
        return 0;
    while (exponent > 0)
    {
        if (exponent & 1)
            result = (result * base) % mod;
        exponent = exponent >> 1;
        base     = (base * base) % mod;
    }
    return result % mod;
}

uint64_t encrypt_byte(const byte_t m, const rsa_exp_t pub_exp, const uint64_t mod)
{
    uint64_t c;

    c = mod_exp(m, pub_exp, mod);
    return c;
}

byte_t decrypt_byte(const uint64_t c, const rsa_exp_t priv_exp, const uint64_t mod)
{
    byte_t m;

    m = mod_exp(c, priv_exp, mod);
    return m;
}

encrypted_byte_array_t encrypt_bytes(const byte_array_t *const bytes, const rsa_exp_t pub_exp, const uint64_t mod)
{
    encrypted_byte_array_t encrypted;

    encrypted = init_encrypted_array(bytes->size);
    for (size_t i = 0; i < bytes->size; i++)
        encrypted.data[i] = encrypt_byte(bytes->data[i], pub_exp, mod);
    return encrypted;
}

byte_array_t decrypt_bytes(const encrypted_byte_array_t *const bytes, const rsa_exp_t priv_exp, const uint64_t mod)
{
    byte_array_t decrypted;

    decrypted = init_byte_array(bytes->size);
    for (size_t i = 0; i < bytes->size; i++)
        decrypted.data[i] = decrypt_byte(bytes->data[i], priv_exp, mod);
    return decrypted;
}

byte_array_t format_encrypted_bytes(const encrypted_byte_array_t *const bytes)
{
    byte_array_t formatted;

    formatted = init_byte_array(bytes->size * (sizeof(encrypted_byte_t) / sizeof(byte_t)));
    for (size_t i = 0; i < formatted.size; i++)
        formatted.data[i] = ((byte_t *)bytes->data)[i];
    return formatted;
}

encrypted_byte_array_t format_bytes(const byte_array_t *const bytes)
{
    encrypted_byte_array_t formatted;

    formatted = init_encrypted_array(bytes->size / (sizeof(encrypted_byte_t) / sizeof(byte_t)));
    for (size_t i = 0; i < formatted.size; i++)
        formatted.data[i] = ((encrypted_byte_t *)bytes->data)[i];
    return formatted;
}
