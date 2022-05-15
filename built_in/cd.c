#include "../inc/minishell.h"

int blt_cd(char *path, char ***env)
{
    int all;

    all = 0;
    if (!path || (path[0] == '~' && !path[1]))
    {
        path = find_var(ft_strdup("HOME"), *env);
        all = 1;
    }
    else if (blt_pwd() && !ft_strncmp(path, ".", 2))
    {
        printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory");
        return (1);
    }
    else if (chdir(path) == -1)
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