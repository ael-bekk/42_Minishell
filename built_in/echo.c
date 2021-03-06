/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 04:00:51 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 04:01:01 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_all(char **cmd, int fd_out)
{
	int	i;

	i = -1;
	while (cmd && cmd[++i])
	{
		ft_putstr_fd(cmd[i], fd_out);
		if (cmd[i + 1])
			ft_putstr_fd(" ", fd_out);
	}
}

int	nl_echo(char *s)
{
	int	i;

	i = 0;
	while (s && s[0] == '-' && s[++i])
		if (s[i] != 'n')
			return (0);
	if (s && s[1] == 'n' && !s[i])
		return (1);
	return (0);
}

int	blt_echo(char **cmd, int fd_out)
{
	int	i;

	i = 0;
	while (cmd && cmd[i] && nl_echo(cmd[i]))
		i++;
	print_all(&cmd[i], fd_out);
	if (!nl_echo(cmd[0]) && (cmd[i] || !i))
		ft_putstr_fd("\n", fd_out);
	else if (cmd[i] && cmd[i][ft_strlen(cmd[i]) - 1] != '\n'
		&& nl_echo(cmd[0]) && fd_out == 1)
		g_glob.no_nl = 1;
	return (0);
}
