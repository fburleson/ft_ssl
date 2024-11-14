#include "ft_ssl.h"
#include <stdio.h>

typedef struct rsa_opts_s
{
        char *inform;
        char *outform;
        bool  des;
        bool  text;
        bool  noout;
        bool  modulus;
        bool  check;
        bool  pubin;
        bool  pubout;
} rsa_opts_t;

static rsa_opts_t init_opts(const cmd_t *const cmd)
{
    option_t  *current_opt;
    rsa_opts_t opts;

    opts.outform = NULL;
    opts.inform  = NULL;
    opts.des     = false;
    opts.text    = false;
    opts.noout   = false;
    opts.modulus = false;
    opts.check   = false;
    opts.pubin   = false;
    opts.pubout  = false;
    for (size_t i = 0; i < cmd->n_options; i++)
    {
        current_opt = cmd->options[i];
        if (ft_strequals(current_opt->name, "inform"))
        {
            if (current_opt->n_args == 0)
                option_wrn_msg(current_opt, WRN_MSG_OPT_NO_ARG);
            else
                opts.inform = current_opt->args[0];
        }
        else if (ft_strequals(current_opt->name, "outform"))
        {
            if (current_opt->n_args == 0)
                option_wrn_msg(current_opt, WRN_MSG_OPT_NO_ARG);
            else
                opts.outform = current_opt->args[0];
        }
        else if (ft_strequals(current_opt->name, "des"))
            opts.des = true;
        else if (ft_strequals(current_opt->name, "text"))
            opts.text = true;
        else if (ft_strequals(current_opt->name, "noout"))
            opts.noout = true;
        else if (ft_strequals(current_opt->name, "modulus"))
            opts.modulus = true;
        else if (ft_strequals(current_opt->name, "check"))
            opts.check = true;
        else if (ft_strequals(current_opt->name, "pubin"))
            opts.pubin = true;
        else if (ft_strequals(current_opt->name, "pubout"))
            opts.pubout = true;
    }
    return opts;
}

status_t process_rsa(const cmd_t *const cmd)
{
    char      *file_content;
    rsa_opts_t opts;

    opts         = init_opts(cmd);
    file_content = read_file(cmd->inout.in);
    if (!opts.noout)
    {
        print_str_fd("writing RSA key\n", cmd->inout.out);
        print_str_fd(file_content, cmd->inout.out);
    }
    free(file_content);
    return OK;
}
