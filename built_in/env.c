#include "../inc/minishell.h"

int    blt_env(char *s, int fd_out)
{
    t_list *lst;

    if (s)
    {
        ft_putstr_fd("env: ", 2);
        ft_putstr_fd(s, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        glob.exit_code = 1;
        return (1);
    }
    lst = glob.env;
	while (lst)
	{
		ft_putstr_fd(lst->key, fd_out);
        ft_putstr_fd("=", fd_out);
        ft_putstr_fd(lst->value, fd_out);
        ft_putstr_fd("\n", fd_out);
		lst = lst->next;
	}
    return (0);
}