#include "../inc/minishell.h"

int     blt_pwd()
{
    char    *s;

    s = getcwd(NULL, 0);
    printf("%s\n", s);
    free(s);
    return (0);
}