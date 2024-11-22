#include "ft_ssl.h"
#include <stdio.h>

byte_array_t encode(const int fd)
{
    off_t        size;
    byte_array_t encoded;
    ssize_t      total_bytes_read;
    ssize_t      bytes_read;

    encoded.size     = 0;
    encoded.data     = NULL;
    size             = file_len(fd);
    bytes_read       = 0;
    total_bytes_read = 0;
    if (size == -1)
        return encoded;
    encoded = init_byte_array(size);
    do
    {
        bytes_read = read(fd, encoded.data, encoded.size);
        total_bytes_read += bytes_read;
        if (bytes_read == -1)
        {
            free_byte_array(&encoded);
            return encoded;
        }
    } while (bytes_read < size);
    return encoded;
}
