/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:07:33 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/05/29 01:26:48 by amounadi         ###   ########.fr       */
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
