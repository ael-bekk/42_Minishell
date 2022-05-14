#include "../inc/minishell.h"

int blt_cd(char *path, char **env)
{
    int all;

    all = 0;
    if (!path || (path[0] == '~' && !path[1]))
    {
        path = find_var(ft_strdup("HOME"), env);
        all = 1;
    }
    if (chdir(path) == -1)
    {
        printf("Minishell: cd: %s: %s\n", path, strerror(errno));
        if (all)
            free(path);
        return (1);
    }
    if (all)
            free(path);
    return (0);
}