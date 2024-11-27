#include "ft_ssl.h"

int main(const int argc, const char **argv)
{
    cmd_t    cmd;
    status_t status;

    if (argc == 1)
    {
        error_msg(ERR_MSG_NO_ARGS);
        return NO_ARGS;
    }
    status = OK;
    cmd    = init_cmd(argc, argv);
    if (ft_strequals(cmd.name, CMD_GEN_RSA))
        status = process_genrsa(&cmd);
    else if (ft_strequals(cmd.name, CMD_RSA))
        status = process_rsa(&cmd);
    else if (ft_strequals(cmd.name, CMD_RSA_UTL))
        status = process_rsautl(&cmd);
    else
    {
        error_msg(ERR_MSG_INV_ARG);
        status = INV_ARG;
    }
    clean_cmd(&cmd);
    return status;
}
