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

#define WRN_MSG_PREFIX        "warning: "
#define WRN_MSG_OPT_NO_ARG    "no argument given"
#define WRN_MSG_OPT_INV_ARG   "invalid argument given"
#define WRN_MSG_OPT_INV       "invalid option given"

#define ERR_MSG_PREFIX        "error: "
#define ERR_MSG_NO_ARGS       "no arguments given"
#define ERR_MSG_INV_ARG       "invalid argument given"

#define CMD_GEN_RSA           "genrsa"
#define CMD_RSA_UTL           "rsautl"

typedef uint64_t    rsa_exp_t;
typedef char        byte_t;
typedef uint64_t    encrypted_byte_t;
typedef char        base64_digit_t;
typedef char       *base64_t;
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

typedef struct byte_array_s
{
        byte_t *data;
        size_t  size;
} byte_array_t;

typedef struct encrypted_byte_array_s
{
        encrypted_byte_t *data;
        size_t            size;
} encrypted_byte_array_t;

typedef enum Status
{
    OK,
    NO_ARGS,
    INV_ARG,
    UKNOWN
} status_t;

//  rsa key gen

uint64_t               gen_prime(void);
rsa_exp_t              gen_priv_exp(const uint64_t pub_key, const uint64_t totient);
priv_key_t             gen_priv_key(const rsa_exp_t pub_key);

//  encryption and decryption

byte_array_t           encode(const int fd);
encrypted_byte_t       encrypt_byte(const byte_t byte, const rsa_exp_t pub_exp, uint64_t mod);
byte_t                 decrypt_byte(const encrypted_byte_t encrypted, const rsa_exp_t priv_exp, uint64_t mod);
byte_array_t           encrypt_bytes(const byte_array_t *const bytes, const rsa_exp_t pub_exp, const uint64_t mod);
byte_array_t           decrypt_bytes(const byte_array_t *const bytes, const rsa_exp_t priv_exp, const uint64_t mod);
off_t                  file_len(const int fd);
byte_array_t           read_encrypted_file(const int fd);

//  bytes array

byte_array_t           init_byte_array(const size_t size);
encrypted_byte_array_t init_encrypted_array(const size_t size);
void                   free_byte_array(byte_array_t *const array);
void                   free_encrypted_array(encrypted_byte_array_t *const array);

//  math

uint64_t               totient(const uint64_t p, const uint64_t q);

//  base64

base64_t               dec_to_base64(const uint64_t a);
uint64_t               base64_to_dec(const base64_t base64);

//  string

size_t                 ft_strlen(const char *s);
bool                   ft_strequals(const char *s0, const char *s1);
char                  *ft_strdup(const char *s);

//  random

int                    get_random_dev(void);
uint64_t               read_random_bytes(const int random_dev);
uint64_t               rand_ui64(const int random_dev);
uint64_t               rand_range_ui64(const int random_dev, const uint64_t min, const uint64_t max);

//  error

void                   error_msg(const char *msg);
void                   warning_msg(const char *msg);
#endif
