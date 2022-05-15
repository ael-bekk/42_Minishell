#include "../inc/minishell.h"

int     blt_pwd()
{
    char    *s;

    s = getcwd(NULL, 0);
    if (s)
        printf("%s\n", s);
    else
        return (1);
    free(s);
    return (0);
}