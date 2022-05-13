#include "../inc/minishell.h"

int blt_cd(char *path)
{
    if (chdir(path) == -1)
    {
        printf("Minishell: cd: %s: %s\n", path, strerror(errno));
        return (1);
    }
    return (0);
}