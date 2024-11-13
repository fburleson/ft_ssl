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

typedef int         status_t;
typedef uint64_t    rsa_exp_t;
typedef uint8_t     byte_t;
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

enum Status
{
    OK,
    NO_ARGS,
    INV_ARG,
    UKNOWN
};

//  rsa key gen

uint64_t   gen_prime(void);
rsa_exp_t  gen_priv_exp(const uint64_t pub_key, const uint64_t totient);
priv_key_t gen_priv_key(const rsa_exp_t pub_key);

//  encryption and decryption

uint64_t   encrypt_byte(const byte_t byte, const rsa_exp_t pub_exp, uint64_t mod);
byte_t     decrypt_byte(const uint64_t encrypted, const rsa_exp_t priv_exp, uint64_t mod);

//  math

uint64_t   totient(const uint64_t p, const uint64_t q);

//  string

size_t     ft_strlen(const char *s);
bool       ft_strequals(const char *s0, const char *s1);
char      *ft_strdup(const char *s);

//  random

int        get_random_dev(void);
uint64_t   read_random_bytes(const int random_dev);
uint64_t   rand_ui64(const int random_dev);
uint64_t   rand_range_ui64(const int random_dev, const uint64_t min, const uint64_t max);

//  error

void       error_msg(const char *msg);
void       warning_msg(const char *msg);
#endif
