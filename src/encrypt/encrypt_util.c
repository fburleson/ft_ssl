#include "ft_ssl.h"

encrypted_array_t read_encrypted_file(const int fd)
{
    off_t             size;
    encrypted_array_t bytes;

    size  = file_len(fd);
    bytes = init_encrypted_array(size);
    read(fd, bytes.data, size);
    return bytes;
}
