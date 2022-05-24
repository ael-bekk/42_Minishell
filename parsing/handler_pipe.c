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
		{
			a = 0;
			if ((str[i + 1] && str[i + 1] == '|') || ( str[i - 1] && str[i - 1] == '|'))
				a = 1;
		}
		else  if (str[i] != ' ' && str[i] != '\n')
			a = 1;
	}
	return(a);
}


int	check_all2(char a, char s , int i, int y)
{

	if(a == '|' && s == '&')
		return(0); 
	if (a == '&' && s == '|')
		return (0);
	return (1);
}

int check_all(char *line)
{
	int i;
	int a;
	int y;
	int lent;
	
	i = 0;
	if (!line)
		return (0);
	lent =ft_strlen(line);
	while(i < lent)
	{
		while(line[i] && (line[i] == '\n' || line[i] == ' '))
			i++;
		if (line[i + 1]  && line[i] && (line[i] == '|' || (line[i] == '&' && line[i + 1] !='&')))
		{
			a = line[i];
			i++;
			y = i;
			while(line[i] && (line[i] == '\n' || line[i] == ' '))
				i++;
			if(line[i] && !check_all2(a, line[i], i, y))
			{
				ft_putstr_fd("Minishell : syntax error near unexpected token \n",2);
				glob.exit_code = 258;
				return (0);
			}
		}
		i++;
	}
	return (1);
}

char *handler_pipe(char *line)
{
	char *str;
	int 	a;

	if (!line)
		return (NULL);	
	a = !check_pipe(line);
	free(glob.herd);
	glob.herd = NULL;
	glob.herd = ft_strdup("\033[0;32mpipe> \033[0;37m");
	while (a)
	{
		str = readline(glob.herd);
		if (!str)
		{
			if (!glob.no_init)
				ft_putstr_fd("\033[4;31m Minishell: syntax error: unexpected end of file\n\033[0m", 2);
			glob.no_init = 1;
			free(line);
			free(str);
			return (NULL);
		}
		line = ft_strjoin_freed2(line, str, 1);
		if (check_pipe(line))
			a = 0;
	}
	return (line);
}

char *check_full(char *line)
{
	int v;
	int a;
	
	if (!line)
		return (NULL);
	v = !check_pipe(line) ||  check_quote(line);
	if (!v)
		a = check_or_and(line);
	while (v || a == -1 || a == 0)
	{
		line = handel_quote(line);
		line = handler_pipe(line);
		if (!check_all(line))
			return (NULL);
		line = handler_or_and(line);
		if (!check_all(line))
			return (NULL);
		v = !check_pipe(line) || check_quote(line);
		if (!v)
			a = check_or_and(line);
	}
	return (line);
}
