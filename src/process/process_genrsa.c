#include "ft_ssl.h"

static void print_base64(const uint64_t a, const int fd)
{
    base64_t base64;

    base64 = dec_to_base64(a);
    write(fd, base64, BASE64_N_DIGITS);
    free(base64);
}

status_t process_genrsa(const cmd_t *const cmd)
{
    priv_key_t priv_key;

    priv_key = gen_priv_key(DEFAULT_PUB_EXP);
    write(cmd->inout.out, PRIV_KEY_BEGIN, ft_strlen(PRIV_KEY_BEGIN));
    print_base64(priv_key.p, cmd->inout.out);
    print_base64(priv_key.q, cmd->inout.out);
    print_base64(priv_key.p * priv_key.q, cmd->inout.out); // mod
    print_base64(priv_key.pub_exp, cmd->inout.out);
    print_base64(priv_key.priv_exp, cmd->inout.out);
    write(cmd->inout.out, "\n", 1);
    write(cmd->inout.out, PRIV_KEY_END, ft_strlen(PRIV_KEY_END));
    return OK;
}
