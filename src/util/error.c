#include "ft_ssl.h"
#include <unistd.h>

void error_msg(const char *msg)
{
    print_str_fd(ERR_MSG_PREFIX, STDERR_FILENO);
    print_str_fd(msg, STDERR_FILENO);
    print_str_fd(".\n", STDERR_FILENO);
}

void warning_msg(const char *msg)
{
    print_str_fd(WRN_MSG_PREFIX, STDERR_FILENO);
    print_str_fd(msg, STDERR_FILENO);
    print_str_fd(".\n", STDERR_FILENO);
}
