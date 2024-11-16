#include "ft_ssl.h"
#include <unistd.h>

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

static void print_text(const rsa_opts_t *const opts, const hybrid_key_t *const key)
{
    if (opts->pubout)
        print_pub_key_text(&key->pub_key, STDOUT_FILENO);
    else
        print_priv_key_text(&key->priv_key, STDOUT_FILENO);
}

static void print_modulus(const hybrid_key_t *const key)
{
    base16_t hex;

    hex = dec_to_base16(key->priv_key.mod);
    print_str_fd("modulus=0x", STDOUT_FILENO);
    print_str_fd(hex, STDOUT_FILENO);
    print_str_fd("\n", STDOUT_FILENO);
    free(hex);
}

static void print_key(const cmd_t *const cmd, const rsa_opts_t *const opts, const hybrid_key_t *const key)
{
    print_str_fd("writing RSA key\n", STDOUT_FILENO);
    if (!opts->pubin)
    {
        if (!opts->pubout)
            print_priv_key(&key->priv_key, cmd->inout.out);
        else
            print_pub_key(&key->pub_key, cmd->inout.out);
    }
    else
        print_pub_key(&key->pub_key, cmd->inout.out);
}

status_t process_rsa(const cmd_t *const cmd)
{
    char        *file_content;
    rsa_opts_t   opts;
    hybrid_key_t key;

    opts         = init_opts(cmd);
    file_content = read_file(cmd->inout.in);
    if (opts.pubin)
        opts.pubout = true;
    if (!opts.pubin)
        key.priv_key = parse_priv_key(file_content);
    else
        key.pub_key = parse_pub_key(file_content);
    if (opts.text)
        print_text(&opts, &key);
    if (opts.modulus)
        print_modulus(&key);
    if (!opts.noout)
        print_key(cmd, &opts, &key);
    free(file_content);
    return OK;
}
