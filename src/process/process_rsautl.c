#include "ft_ssl.h"

typedef struct rsautl_opts_s
{
        int  inkey;
        bool pubin;
        bool encrypt;
        bool decrypt;
        bool hexdump;
} rsautl_opts_t;

static rsautl_opts_t init_opts(const cmd_t *const cmd)
{
    option_t     *current_opt;
    rsautl_opts_t opts;

    opts.inkey   = -1;
    opts.pubin   = false;
    opts.encrypt = false;
    opts.decrypt = false;
    opts.hexdump = false;
    for (size_t i = 0; i < cmd->n_options; i++)
    {
        current_opt = cmd->options[i];
        if (ft_strequals(current_opt->name, "inkey"))
        {
            if (current_opt->n_args == 0)
                option_wrn_msg(current_opt, WRN_MSG_OPT_NO_ARG);
            else
                opts.inkey = process_file_opt(current_opt, O_RDONLY, STDIN_FILENO);
        }
        else if (ft_strequals(current_opt->name, "pubin"))
            opts.pubin = true;
        else if (ft_strequals(current_opt->name, "encrypt"))
            opts.encrypt = true;
        else if (ft_strequals(current_opt->name, "decrypt"))
            opts.decrypt = true;
        else if (ft_strequals(current_opt->name, "hexdump"))
            opts.hexdump = true;
    }
    return opts;
}

static void process_encryption(const pub_key_t *const pub_key, const int in, const int out)
{
    byte_array_t content;
    byte_array_t encrypted;

    content = encode(in);
    if (!content.data)
        return;
    encrypted = encrypt_bytes(&content, pub_key->pub_exp, pub_key->mod);
    write(out, encrypted.data, encrypted.size);
    free_byte_array(&content);
}

static void process_decryption(const priv_key_t *const priv_key, const int in, const int out)
{
    byte_array_t content;
    byte_array_t decrypted;

    content = read_encrypted_file(in);
    if (!content.data)
        return;
    decrypted = decrypt_bytes(&content, priv_key->priv_exp, priv_key->mod);
    write(out, decrypted.data, decrypted.size);
    free_byte_array(&content);
}

status_t process_rsautl(const cmd_t *const cmd)
{
    rsautl_opts_t opts;
    hybrid_key_t  key;
    char         *key_content;

    opts = init_opts(cmd);
    if (opts.decrypt && opts.encrypt)
    {
        error_msg("options 'decrypt' and 'encrypt' are mutaully exclusive.");
        return INV_ARG;
    }
    else if (!opts.decrypt && !opts.encrypt)
    {
        error_msg("option 'decrypt' or 'encrypt' is mandatory");
        return INV_ARG;
    }
    if (!opts.inkey)
    {
        error_msg("no key specified");
        return INV_ARG;
    }
    key_content = read_file(opts.inkey);
    if (opts.pubin)
        key.pub_key = parse_pub_key(key_content);
    else
        key.priv_key = parse_priv_key(key_content);
    if (opts.encrypt)
        process_encryption(&key.pub_key, cmd->inout.in, cmd->inout.out);
    else if (opts.decrypt)
        process_decryption(&key.priv_key, cmd->inout.in, cmd->inout.out);
    free(key_content);
    return OK;
}
