#include "ft_ssl.h"

off_t file_len(const int fd)
{
    fstat_t file_stat;

    if (fstat(fd, &file_stat) == -1)
        return -1;
    return file_stat.st_size;
}

byte_array_t read_encrypted_file(const int fd)
{
    byte_array_t bytes;

    bytes = init_byte_array(file_len(fd));
    for (size_t i = 0; i < bytes.size; i++)
        read(fd, bytes.data + i, 1);
    return bytes;
}
