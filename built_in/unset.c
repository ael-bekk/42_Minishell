#include "../inc/minishell.h"

int blt_unset(char **cmd, char **env)
{
    int i;
    int j;

    i = -1;
    while (cmd && cmd[++i])
    {
        j = -1;
        while (env && env[++j])
        {
            if (!ft_strncmp(cmd[i], env[j], strlen(cmd[i])) && env[j][strlen(cmd[i])] == '=')
            {
                free(env[j]);
                env[j] = NULL;
                while (env[++j])
                    env[j - 1] = env[j];
                env[--j] = NULL;
            }
        }
    }
    return (0);
}