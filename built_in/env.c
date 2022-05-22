#include "../inc/minishell.h"

int    blt_env(t_cmd *cmd)
{
    char **env;
    int i;

    i = 0;
    env = list_to_str();
    if (cmd->cmd[1])
    {
        ft_putstr_fd("env: ",2);
        ft_putstr_fd(cmd->cmd[1],2);
        ft_putstr_fd(": No such file or directory\n",2);
        glob.exit_code = 127;
        return (127);
    }
    while(env[i])
    {
        ft_putstr_fd(env[i++],cmd->out);
        ft_putstr_fd("\n",cmd->out);
    }
    return (0);
}
