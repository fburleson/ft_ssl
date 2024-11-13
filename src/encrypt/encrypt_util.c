#include "ft_ssl.h"

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

off_t file_len(const int fd)
{
    fstat_t file_stat;

    if (fstat(fd, &file_stat) == -1)
        return -1;
    return file_stat.st_size;
}

encrypted_byte_array_t read_encrypted_file(const int fd)
{
    byte_array_t           bytes;
    encrypted_byte_array_t encrypted;

    bytes = init_byte_array(file_len(fd));
    for (size_t i = 0; i < bytes.size; i++)
        read(fd, bytes.data + i, 1);
    encrypted = format_bytes(&bytes);
    free_byte_array(&bytes);
    return encrypted;
}
