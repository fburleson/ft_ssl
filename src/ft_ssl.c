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
    else
    {
        error_msg(ERR_MSG_INV_ARG);
        status = INV_ARG;
    }
    free_cmd(&cmd);
    return status;
}

// int main(void)
// {
//     byte_t     m;
//     uint64_t   encrypted;
//     byte_t     decrypted;
//     priv_key_t priv_key;
//     uint64_t   mod;
//
//     priv_key  = gen_priv_key(DEFAULT_PUB_EXP);
//     mod       = priv_key.q * priv_key.p;
//     m         = 10;
//     encrypted = encrypt_byte(m, priv_key.pub_exp, mod);
//     decrypted = decrypt_byte(encrypted, priv_key.priv_exp, mod);
//     printf("priv_exp:   %lu\n", priv_key.priv_exp);
//     printf("decrypted:  %u\n", decrypted);
// }

// int main(void)
// {
//     priv_key_t   priv_key;
//     uint64_t     mod;
//     int          fd;
//     byte_array_t bytes;
//     byte_array_t encrypted;
//     byte_array_t decrypted;
//
//     priv_key  = gen_priv_key(DEFAULT_PUB_EXP);
//     mod       = priv_key.q * priv_key.p;
//     fd        = open(".gitignore", O_RDONLY);
//     bytes     = encode(fd);
//     encrypted = encrypt_bytes(&bytes, priv_key.pub_exp, mod);
//     decrypted = decrypt_bytes(&encrypted, priv_key.priv_exp, mod);
//     for (size_t i = 0; i < bytes.size; i++)
//         printf("%c", bytes.data[i]);
//     printf("\n----- ENCRYPTED -----\n");
//     for (size_t i = 0; i < encrypted.size; i++)
//         printf("%c", encrypted.data[i]);
//     printf("\n----- DECRYPTED -----\n");
//     for (size_t i = 0; i < decrypted.size; i++)
//         printf("%c", decrypted.data[i]);
//     printf("\n----- PRIVATE KEY -----\n");
//     printf("%lu\n", priv_key.priv_exp);
// }

// int main(void)
// {
//     base64_t base64;
//     uint64_t base10;
//
//     base64 = dec_to_base64(12);
//     base10 = base64_to_dec(base64);
//     printf("%s\n", base64);
//     printf("%lu\n", base10);
//     free(base64);
// }

// int main(void)
// {
//     priv_key_t   priv_key;
//     uint64_t     mod;
//     int          fd;
//     int          encrypted_fd;
//     byte_array_t bytes;
//     byte_array_t encrypted;
//     byte_array_t read_encrypted;
//     byte_array_t decrypted;
//
//     priv_key     = gen_priv_key(DEFAULT_PUB_EXP);
//     mod          = priv_key.p * priv_key.q;
//     fd           = open(".gitignore", O_RDONLY);
//     encrypted_fd = open("encrypted", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     bytes        = encode(fd);
//     encrypted    = encrypt_bytes(&bytes, priv_key.pub_exp, mod);
//     write(encrypted_fd, encrypted.data, encrypted.size);
//     close(encrypted_fd);
//     encrypted_fd   = open("encrypted", O_RDONLY);
//     read_encrypted = read_encrypted_file(encrypted_fd);
//     decrypted      = decrypt_bytes(&read_encrypted, priv_key.priv_exp, mod);
//     for (size_t i = 0; i < decrypted.size; i++)
//         printf("%c", decrypted.data[i]);
// }
