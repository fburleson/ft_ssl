#include "ft_ssl.h"

status_t process_genrsa(const cmd_t *const cmd)
{
    priv_key_t priv_key;

    priv_key = gen_priv_key(DEFAULT_PUB_EXP);
    print_priv_key(&priv_key, cmd->inout.out);
    return OK;
}
