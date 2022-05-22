#include "../inc/minishell.h"

void print_all(char **cmd ,t_cmd *c)
{
    int i;

    i = -1;
    while (cmd && cmd[++i])
    {
        ft_putstr_fd(cmd[i],c->out);
        if (cmd[i + 1])
            ft_putstr_fd(" ",c->out);
    }
}

int nl_echo(char *s)
{
    int i;

    i = 0;
    while (s && s[0] == '-'&& s[++i])
        if (s[i] != 'n')
            return (0);
    if (s && s[1] == 'n' && !s[i])
        return (1);
    return (0);
}
int blt_echo(t_cmd *cmd)
{
    int i;

    i = 1;
    if (!cmd->cmd[1])
    {
        ft_putstr_fd("\n",cmd->out);
        return (0);
    }
    while (cmd->cmd[1] && cmd->cmd[i] && nl_echo(cmd->cmd[i]))
        i++;
    print_all(&cmd->cmd[i],cmd);
    if (!nl_echo(cmd->cmd[1]) && (cmd->cmd[i] || !i))
        ft_putstr_fd("\n",cmd->out);
    /*else if (cmd->cmd[i] && cmd->cmd[i][ft_strlen(cmd->cmd[i]) - 1] != '\n' && nl_echo(cmd->cmd[1]))
            ft_putstr_fd("%\n",cmd->out);*/
    return (0);
}
