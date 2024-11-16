#ifndef FT_SSL_H
#define FT_SSL_H

#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define DEFAULT_PUB_EXP       65537
#define MILLER_RABIN_ERR_PROB 0.25f
#define PRIME_NUM_PROBABILITY 0.75f
#define MIN_PRIME             10000
#define MAX_PRIME             65537

#define PRIV_KEY_BEGIN        "-----BEGIN RSA PRIVATE KEY-----\n"
#define PRIV_KEY_END          "-----END RSA PRIVATE KEY-----\n"
#define PUB_KEY_BEGIN         "-----BEGIN RSA PUBLIC KEY-----\n"
#define PUB_KEY_END           "-----END RSA PUBLIC KEY-----\n"

#define BASE64_N_DIGITS       11
#define BASE16_N_DIGITS       16

#define READ_BUFF_SIZE        1024

#define WRN_MSG_PREFIX        "warning: "
#define WRN_MSG_OPT_NO_ARG    "no argument given"
#define WRN_MSG_OPT_INV_ARG   "invalid argument given"
#define WRN_MSG_OPT_INV       "invalid option given"

#define ERR_MSG_PREFIX        "error: "
#define ERR_MSG_NO_ARGS       "no arguments given"
#define ERR_MSG_INV_ARG       "invalid argument given"

#define CMD_GEN_RSA           "genrsa"
#define CMD_RSA_UTL           "rsautl"
#define CMD_RSA               "rsa"

typedef uint64_t    rsa_exp_t;
typedef char        byte_t;
typedef uint64_t    encrypted_byte_t;
typedef char        base64_digit_t;
typedef char        base16_digit_t;
typedef char       *base64_t;
typedef char       *base16_t;
typedef struct stat fstat_t;

typedef struct priv_key_s
{
        uint64_t  p;
        uint64_t  q;
        rsa_exp_t pub_exp;
        rsa_exp_t priv_exp;
} priv_key_t;

typedef struct pub_key_s
{
        uint64_t  p;
        uint64_t  q;
        rsa_exp_t pub_exp;
} pub_key_t;

typedef union hyrid_key_t
{
        priv_key_t priv_key;
        pub_key_t  pub_key;
} hybrid_key_t;

typedef struct byte_array_s
{
        byte_t *data;
        size_t  size;
} byte_array_t;

typedef struct option_s
{
        char   *name;
        char  **args;
        uint8_t n_args;
} option_t;

typedef struct inout_s
{
        int in;
        int out;
} inout_t;

typedef struct cmd_s
{
        char      *name;
        option_t **options;
        uint8_t    n_options;
        inout_t    inout;
} cmd_t;

typedef enum Status
{
    OK,
    NO_ARGS,
    INV_ARG,
    UKNOWN
} status_t;

//  process

cmd_t            init_cmd(const uint32_t argc, const char **argv);
void             free_cmd(const cmd_t *const cmd);
void             option_wrn_msg(const option_t *const option, const char *msg);
inout_t          init_inout(const cmd_t *const cmd);
int              process_file_opt(const option_t *const option, const int flags, const int fallback);
status_t         process_genrsa(const cmd_t *const cmd);
status_t         process_rsa(const cmd_t *const cmd);

//  key util

priv_key_t       parse_priv_key(const char *content);
pub_key_t        parse_pub_key(const char *content);
void             print_priv_key(const priv_key_t *const priv_key, const int fd);
void             print_pub_key(const pub_key_t *const pub_key, const int fd);

//  rsa key gen

uint64_t         gen_prime(void);
rsa_exp_t        gen_priv_exp(const uint64_t pub_key, const uint64_t totient);
priv_key_t       gen_priv_key(const rsa_exp_t pub_key);

//  encryption and decryption

byte_array_t     encode(const int fd);
encrypted_byte_t encrypt_byte(const byte_t byte, const rsa_exp_t pub_exp, uint64_t mod);
byte_t           decrypt_byte(const encrypted_byte_t encrypted, const rsa_exp_t priv_exp, uint64_t mod);
byte_array_t     encrypt_bytes(const byte_array_t *const bytes, const rsa_exp_t pub_exp, const uint64_t mod);
byte_array_t     decrypt_bytes(const byte_array_t *const bytes, const rsa_exp_t priv_exp, const uint64_t mod);
off_t            file_len(const int fd);
byte_array_t     read_encrypted_file(const int fd);

//  bytes array

byte_array_t     init_byte_array(const size_t size);
void             free_byte_array(byte_array_t *const array);

//  math

uint64_t         totient(const uint64_t p, const uint64_t q);
uint64_t         key_mod(const uint64_t p, const uint64_t q);

//  base64

base64_t         dec_to_base64(const uint64_t a);
uint64_t         base64_to_dec(const base64_t base64);

//  base16

base16_t         dec_to_base16(const uint64_t a);
uint64_t         base16_to_dec(const base16_t base16);

//  file

char            *read_file(const int fd);

//  print

void             print_str_fd(const char *s, const int fd);

//  string

size_t           ft_strlen(const char *s);
bool             ft_strequals(const char *s0, const char *s1);
char            *ft_strdup(const char *s);
char            *ft_strcat(const char *s0, const char *s1);

//  random

int              get_random_dev(void);
uint64_t         read_random_bytes(const int random_dev);
uint64_t         rand_ui64(const int random_dev);
uint64_t         rand_range_ui64(const int random_dev, const uint64_t min, const uint64_t max);

//  error

void             error_msg(const char *msg);
void             warning_msg(const char *msg);
#endif
