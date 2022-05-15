#include "../inc/minishell.h"


void print_all(char **cmd)
{
    int i;

    i = -1;
    while (cmd && cmd[++i])
    {
        printf("%s", cmd[i]);
        if (cmd[i + 1])
            printf(" ");
    }
}

int nl_echo(char *s)
{
    int i;

    i = 0;
    while (s && s[0] == '-' && s[++i])
        if (s[i] != 'n')
            return (0);
    if (s && !s[i])
        return (1);
    return (0);
}

int blt_echo(char **cmd)
{
    int i;

    i = 0;
    while (cmd && cmd[i] && nl_echo(cmd[i]))
        i++;
    print_all(&cmd[i]);
    if (nl_echo(cmd[0]))
        printf("\033[0;106m%%\033[0m");
    printf("\n");
    return (0);
}