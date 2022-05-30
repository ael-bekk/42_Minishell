/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 04:02:01 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 04:02:06 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_print_error(void)
{
	ft_putstr_fd("pwd: too many arguments\n", 2);
	glob.exit_code = 1;
	return (1);
}

int	blt_pwd(char *p, int fd_out)
{
	char	*s;
	t_list	*l;

	if (p)
		return (ft_print_error());
	s = getcwd(NULL, 0);
	if (s)
	{
		ft_putstr_fd(s, fd_out);
		ft_putstr_fd("\n", fd_out);
	}
	else
	{
		l = find_var2("PWD", glob.env);
		if (l)
		{
			ft_putstr_fd(l->value, fd_out);
			ft_putstr_fd("\n", fd_out);
		}
		return (1);
	}
	free(s);
	return (0);
}
