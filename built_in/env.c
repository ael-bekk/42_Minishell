#include "../inc/minishell.h"

int    blt_env(char **cmd)
{
    int i;

    i = -1;
    while (cmd[++i])
        printf("%s\n", cmd[i]);
    return (0);
}