/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 02:58:32 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/14 23:05:56 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int check_pipe(char *str)
{
	int i;
	int a;

	i = -1;
	a = 1;
	if (!str)
		return(1);
	while (str[++i])
	{
		if (str[i] == '|')
			a = 0;
		else  if (str[i] != ' ' && str[i] != '\n')
			a = 1;
	}
	return(a);
}

char *handler_pipe(char *line)
{
	char *str;
	int 	a;

	if (!line)
		return (NULL);	
	a = !check_pipe(line);
	while (a)
	{
		str = readline("\033[0;32mpipe> \033[0;37m");
		if (!str)
		{
			ft_putstr_fd("Minishell: syntax error: unexpected end of file\n", 2);
			free(line);
			return (NULL);
		}
		line = ft_strjoin_freed(line, str, 0);
		if (check_pipe(line))
			a = 0;
	}
	return (line);
}

char *check_full(char *line)
{
	int v;
	
	if (!line)
		return (NULL);
	v = !check_pipe(line) ||  check_quote(line);
	while (v)
	{
		//line = handel_quote2(line);
		line = handel_quote(line);
		line = handler_pipe(line);
		v = !check_pipe(line) || check_quote(line);
	}
	return (line);
}
