#include "libft.h"

void    ft_free(char **s)
{
    int i;

    i = -1;
    while (s && s[++i])
        free(s[i]);
    free(s);
}