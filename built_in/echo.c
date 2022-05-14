#include "../inc/minishell.h"

int blt_echo(char **cmd)
{
    int i;
    int n;
    int j;

    j = 0;
    n = 1;
    i = -1;
    if (cmd[0][++i] == '-')
    {
        while (cmd[0][++i] && cmd[0][i] == 'n')
            ;
        n = cmd[0][i];
    }
    i = -1 * (n != 0);
    while (cmd[++i])
    {
        j = -1;
        while (cmd[i][++j])
            //if (cmd[i][j] != '\n' || n)
                printf("%c", cmd[i][j]);
        if (cmd[i + 1])
            printf(" ");
    }
    if (n)
        printf("\n");
    return (0);
}