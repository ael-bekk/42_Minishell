#include "../inc/minishell.h"

void    affich_env(void *data)
{
    t_list *d;

    d = data;
    printf("%s=%s\n", d->key, d->value);
}

int    blt_env()
{
    ft_lstiter(glob.env, &affich_env);
    return (0);
}