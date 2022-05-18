#include "../inc/minishell.h"

int ft_double_strlen(char **s)
{
    int i;

    i = 0;
    while (s && s[i])
        i++;
    return (i);
}