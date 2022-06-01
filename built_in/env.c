/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:32:25 by amounadi          #+#    #+#             */
/*   Updated: 2022/06/01 17:32:32 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	blt_env(char *s, int fd_out)
{
	int			i;
	char		**str;

	str = list_to_str(g_glob.env);
	if (s)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_glob.exit_code = 1;
		ft_free(str);
		return (1);
	}
	i = -1;
	while (str && str[++i])
	{
		ft_putstr_fd(str[i], fd_out);
		ft_putstr_fd("\n", fd_out);
	}
	ft_free(str);
	return (0);
}
