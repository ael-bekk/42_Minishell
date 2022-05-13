#include "../inc/minishell.h"

int blt_cd(char *path, char **env)
{
    if (!path)
        path = find_var(ft_strdup("HOME"), env);
    if (chdir(path) == -1)
    {
        printf("Minishell: cd: %s: %s\n", path, strerror(errno));
        free(path);
        return (1);
    }
    free(path);
    return (0);
}