#include "ft_ssl.h"

byte_array_t init_byte_array(const size_t size)
{
    byte_array_t bytes;

    bytes.size = size;
    bytes.data = malloc(size * sizeof(byte_t));
    if (!bytes.data)
    {
        bytes.data = NULL;
        bytes.size = 0;
    }
    return bytes;
}

encrypted_byte_array_t init_encrypted_array(const size_t size)
{
    encrypted_byte_array_t bytes;

    bytes.size = size;
    bytes.data = malloc(size * sizeof(encrypted_byte_t));
    if (!bytes.data)
    {
        bytes.data = NULL;
        bytes.size = 0;
    }
    return bytes;
}

void free_byte_array(byte_array_t *const array)
{
    free(array->data);
    array->size = 0;
}

void free_encrypted_array(encrypted_byte_array_t *const array)
{
    free(array->data);
    array->size = 0;
}
