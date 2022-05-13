#include "../inc/minishell.h"

int ft_double_strlen(char **s)
{
    int i;

    i = -1;
    while (s && s[++i])
        ;
    return (i);
}

int blt_export(char **cmd, char ***env)
{
    int i;
    int lent;
    int j;
    char **tmp;

    lent = ft_double_strlen(cmd);
    tmp = *env;
    *env = copy_data(*env, 0);
    //ft_free(tmp);

    i = -1;
    //lent = ft_double_strlen(*env);
    // printf("%d\n", lent);
    // while (cmd && cmd[++i])
    //     *env[lent++] = ft_strdup(cmd[i]);
    // *env[lent] = NULL;
    return (0);
}