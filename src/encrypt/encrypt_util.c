#include "ft_ssl.h"

byte_array_t read_encrypted_file(const int fd)
{
    off_t        size;
    byte_array_t bytes;

    size  = file_len(fd);
    bytes = init_byte_array(size);
    read(fd, bytes.data, size);
    return bytes;
}
