#include "ft_ssl.h"

char *read_file(const int fd)
{
    char    buffer[READ_BUFF_SIZE + 1];
    ssize_t n_bytes;
    char   *temp;
    char   *content;

    content = ft_strdup("");
    do
    {
        n_bytes = read(fd, buffer, READ_BUFF_SIZE);
        if (n_bytes == -1)
        {
            free(content);
            return NULL;
        }
        buffer[n_bytes] = '\0';
        temp            = content;
        content         = ft_strcat(content, buffer);
        free(temp);
    } while (n_bytes);
    return content;
}

off_t file_len(const int fd)
{
    fstat_t file_stat;

    if (fstat(fd, &file_stat) == -1)
        return -1;
    return file_stat.st_size;
}
