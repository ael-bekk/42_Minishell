#include "../inc/minishell.h"


void print_all(char **cmd)
{
    int i;
    int j;

    i = -1;
    while (cmd[++i])
    {
        j = -1;
        while (cmd[i][++j])
            //if (cmd[i][j] != '\n' || n)
                printf("%c", cmd[i][j]);
        if (cmd[i + 1])
            printf(" ");
    }
}

int blt_echo(char **cmd)
{
    int i;
    int n;
    int nl;
    int j;

    n = 0;
    nl = 0;
    i = -1;
    while (cmd[++i] && !n)
    {
        j = -1;
        n = 1;
        if (cmd[i][++j] == '-')
        {
            while (cmd[i][++j] && cmd[i][j] == 'n')
                ;
            n = cmd[i][j];
            nl += !n;
        }
    }
    print_all(&cmd[i - 1]);
    if (!nl)
        printf("\n");
    return (0);
}