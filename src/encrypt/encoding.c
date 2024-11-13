#include "ft_ssl.h"

static off_t file_len(const int fd)
{
    fstat_t file_stat;

    if (fstat(fd, &file_stat) == -1)
        return -1;
    return file_stat.st_size;
}

byte_array_t encode(const int fd)
{
    off_t        size;
    byte_array_t encoded;

    encoded.size = 0;
    encoded.data = NULL;
    size         = file_len(fd);
    if (size == -1)
        return encoded;
    encoded = init_byte_array(size);
    if (read(fd, encoded.data, encoded.size) == -1)
    {
        free_byte_array(&encoded);
        return encoded;
    }
    return encoded;
}
