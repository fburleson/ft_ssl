#include "ft_ssl.h"

void error_msg(const char *msg)
{
    write(STDERR_FILENO, ERR_MSG_PREFIX, ft_strlen(ERR_MSG_PREFIX));
    write(STDERR_FILENO, msg, ft_strlen(msg));
    write(STDERR_FILENO, ".\n", 2);
}

void warning_msg(const char *msg)
{
    write(STDERR_FILENO, WRN_MSG_PREFIX, ft_strlen(WRN_MSG_PREFIX));
    write(STDERR_FILENO, msg, ft_strlen(msg));
    write(STDERR_FILENO, ".\n", 2);
}
