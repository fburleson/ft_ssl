#include "ft_ssl.h"

void print_str_fd(const char *s, const int fd)
{
    write(fd, s, ft_strlen(s));
}
