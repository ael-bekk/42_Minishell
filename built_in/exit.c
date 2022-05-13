#include "../inc/minishell.h"

int    blt_exit(char **cmd)
{
    int i;

    i = -1;
    if (cmd[1])
    {
        while (cmd[1][++i])
        {
            if (!ft_isdigit(cmd[1][i]))
            {
                printf("Minishell: exit: %s: numeric argument required\n", cmd[1]);
                exit(255);
            }
        }
    }
    if (cmd[1] && cmd[2])
    {
        printf("Minishell: exit: too many arguments\n");
        return (1);
    }
    exit(ft_atoi(cmd[1]) % 256);
}