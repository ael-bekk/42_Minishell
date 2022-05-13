#include "../inc/minishell.h"

int blt_echo(char **cmd)
{
    int i;
    int n;

    n = 1;
    i = -1;
    if (cmd[0][++i] == '-')
    {
        while (cmd[0][++i] && cmd[0][i] == 'n')
            ;
        n = cmd[0][i];
    }
    i = -1;
    while (cmd[++i])
        printf("%s ", cmd[i]);
    if (n)
        printf("\n");
    return (0);
}