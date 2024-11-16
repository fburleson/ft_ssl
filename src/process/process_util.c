#include "ft_ssl.h"

inout_t init_inout(const cmd_t *const cmd)
{
    option_t *current_option;
    inout_t   process;

    process.in  = STDIN_FILENO;
    process.out = STDOUT_FILENO;
    for (size_t i = 0; i < cmd->n_options; i++)
    {
        current_option = cmd->options[i];
        if (ft_strequals(current_option->name, "in"))
            process.in = process_file_opt(current_option, O_RDONLY, STDIN_FILENO);
        else if (ft_strequals(current_option->name, "out"))
            process.out = process_file_opt(current_option, O_WRONLY | O_TRUNC | O_CREAT, STDOUT_FILENO);
    }
    return process;
}

int process_file_opt(const option_t *const option, const int flags, const int fallback)
{
    int fd;

    fd = fallback;
    if (option->n_args == 0)
        option_wrn_msg(option, WRN_MSG_OPT_NO_ARG);
    else
    {
        fd = open(option->args[0], flags, 0644);
        if (fd == -1)
        {
            fd = fallback;
            option_wrn_msg(option, WRN_MSG_OPT_INV_ARG);
        }
    }
    return fd;
}

void option_wrn_msg(const option_t *const option, const char *msg)
{
    print_str_fd("opt: ", STDERR_FILENO);
    print_str_fd(option->name, STDERR_FILENO);
    print_str_fd(": ", STDERR_FILENO);
    warning_msg(msg);
}
