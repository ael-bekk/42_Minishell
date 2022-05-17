#include "../inc/minishell.h"

int     blt_pwd()
{
    char    *s;
    t_list  *l;
    s = getcwd(NULL, 0);
    if (s)
        printf("%s\n", s);
    else
    {
        l = find_var2("PWD", glob.env);
        if (l)
            printf("%s\n", l->value);
        return (1);
    }
    free(s);
    return (0);
}