#include "ft_ssl.h"

bool ft_strequals(const char *s0, const char *s1)
{
    size_t i;

    i = 0;
    while (s0[i] && s1[i])
    {
        if (s0[i] != s1[i])
            return false;
        i++;
    }
    if (s0[i] != s1[i])
        return false;
    return true;
}

size_t ft_strlen(const char *s)
{
    size_t len;

    len = 0;
    while (s[len])
        len++;
    return (len);
}

char *ft_strdup(const char *s)
{
    char        *copy;
    unsigned int cidx;

    copy = malloc((ft_strlen(s) + 1) * sizeof(char));
    if (!copy)
        return (NULL);
    cidx = 0;
    while (s[cidx])
    {
        copy[cidx] = s[cidx];
        cidx++;
    }
    copy[cidx] = '\0';
    return copy;
}

char *ft_strcat(const char *s0, const char *s1)
{
    size_t size;
    size_t cidx;
    char  *cat;

    cidx = 0;
    size = ft_strlen(s0) + ft_strlen(s1);
    cat  = malloc((size + 1) * sizeof(char));
    if (!cat)
        return NULL;
    for (size_t j = 0; j < ft_strlen(s0); j++)
    {
        cat[cidx] = s0[j];
        cidx++;
    }
    for (size_t j = 0; j < ft_strlen(s1); j++)
    {
        cat[cidx] = s1[j];
        cidx++;
    }
    cat[size] = '\0';
    return cat;
}
