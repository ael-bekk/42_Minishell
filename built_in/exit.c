/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 04:01:23 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 04:01:25 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	blt_exit(char **cmd)
{
	int	i;

	i = -1;
	if (!cmd[0])
		exit(127);
	while (cmd[0][++i])
	{
		if (!ft_isdigit(cmd[0][i]))
		{
			printf("\033[4;31m %s: exit: %s: numeric argument required\n",
				glob.av[0], cmd[0]);
			exit(255);
		}
	}
	if (cmd[1])
	{
		printf("\033[4;31m %s: exit: too many arguments\n", glob.av[0]);
		return (1);
	}
	exit(ft_atoi(cmd[0]) % 256);
}
