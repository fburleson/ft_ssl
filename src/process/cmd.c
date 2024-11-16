#include "ft_ssl.h"
#include <unistd.h>

static uint8_t n_args(const uint32_t argc, const char **argv, const uint32_t start)
{
    uint32_t cidx;

    cidx = 0;
    while (cidx < argc - start - 1)
    {
        if (argv[start + 1 + cidx][0] == '-')
            break;
        cidx++;
    }
    return cidx;
}

static option_t *init_option(const uint32_t argc, const char **argv, const uint32_t start)
{
    option_t *option;
    uint32_t  cidx;

    option = malloc(sizeof(option_t));
    if (!option)
        return NULL;
    option->name = ft_strdup(&argv[start][1]);
    if (!option->name)
    {
        free(option);
        return NULL;
    }
    option->n_args = n_args(argc, argv, start);
    if (option->n_args == 0)
        return option;
    option->args = malloc(option->n_args * sizeof(char *));
    if (!option->args)
    {
        free(option->name);
        free(option);
        return NULL;
    }
    cidx = 0;
    while (cidx < option->n_args)
    {
        option->args[cidx] = ft_strdup(argv[start + 1 + cidx]);
        cidx++;
    }
    return option;
}

static uint8_t n_options(const uint32_t argc, const char **argv)
{
    uint8_t  n;
    uint32_t cidx;

    n    = 0;
    cidx = 0;
    while (cidx < argc)
    {
        if (argv[cidx][0] == '-')
            n++;
        cidx++;
    }
    return n;
}

cmd_t init_cmd(const uint32_t argc, const char **argv)
{
    cmd_t    cmd;
    uint32_t cidx;
    uint8_t  carg;

    cmd.name = ft_strdup(argv[1]);
    if (!cmd.name)
        return cmd;
    cmd.n_options = n_options(argc, argv);
    cmd.options   = malloc(cmd.n_options * sizeof(option_t *));
    if (!cmd.options)
        return cmd;
    cidx = 2;
    carg = 0;
    while (cidx < argc)
    {
        if (argv[cidx][0] == '-')
        {
            cmd.options[carg] = init_option(argc, argv, cidx);
            carg++;
        }
        cidx++;
    }
    cmd.inout = init_inout(&cmd);
    return cmd;
}

static void free_option(const option_t *const option)
{
    free(option->name);
    for (size_t i = 0; i < option->n_args; i++)
        free(option->args[i]);
}

void clean_cmd(const cmd_t *const cmd)
{
    free(cmd->name);
    for (size_t i = 0; i < cmd->n_options; i++)
        free_option(cmd->options[i]);
    free(cmd->options);
    if (cmd->inout.in != STDIN_FILENO)
        close(cmd->inout.in);
    if (cmd->inout.out != STDOUT_FILENO)
        close(cmd->inout.out);
}
