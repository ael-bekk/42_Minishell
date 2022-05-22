#include "../inc/minishell.h"

int     blt_pwd(t_cmd *cmd)
{
    char    *s;
    t_list  *l;
    s = getcwd(NULL, 0);
    if (s)
    {
        ft_putstr_fd(s,cmd->out);
        ft_putstr_fd("\n",cmd->out);
    }
    else
    {
        l = find_var2("PWD", glob.env);
        if (l)
        {
            ft_putstr_fd(l->value,cmd->out);
            ft_putstr_fd("\n",cmd->out);
        }
        return (1);
    }
    free(s);
    return (0);
}