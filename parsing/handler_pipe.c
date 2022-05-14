/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 02:58:32 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/14 03:01:01 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int check_pipe(char *str)
{
	int i;
	int a;

	i = -1;
	a = 1;
	while (str[++i])
	{
		if (str[i] == '|' && i++)
		{
			a = 0;
			while (str[i] && str[i] != '|' && str[i] != ' ' && i++)
				a = 1;
		}
	}
	return(a);
}

char *handler_pipe(char *line)
{
	char *str;
	int 	a;
	
	a = !check_pipe(line);
	while (a)
	{
		ft_putstr_fd("pipe> ",1);
		str = get_next_line(0);
		line = ft_strjoin_freed(line, str, 1);
		if (check_pipe(line))
			a = 0;
	}
	return (line);
}
