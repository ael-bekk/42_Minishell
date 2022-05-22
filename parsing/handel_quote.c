/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:24:48 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/12 18:28:53 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int check_quote(char *str)
{
	int i = 0;
	int a = 0;
	char c;

	if (!str)
		return(0);
	while(str[i])
	{
		if (!a && (str[i] == '\"' || str[i] == '\''))
		{
			c = str[i];
			a = (str[i] == '\"') + 2 * (str[i] == '\'');
		}
		else if (c == str[i])
			a = 0;
		i++;
	}
	return (a);
}

char *delete_quote(char *str)
{
	int i;
	int j;
	char c;
	char *line;
	int a;

	i = 0;
	j = 0;
	c = 0;
	a = 0;
	if (!str)
		return (NULL);
	line = malloc(ft_strlen(str) + 1);
	while (str && str[i])
	{
		if ((c == 0 || c == str[i]) && (str[i] == '\'' || str[i] == '\"' || str[i] == -2))
		{
			c = str[i++];
			if (++a == 2)
			{
				c = 0;
				a = 0;
			}
		}
		else
			line[j++] = str[i++];
	}
	line[j] = '\0';
	free(str);
	return (line);
}

char *handel_quote(char *line)
{
	char *str;
	int a = 1;

	a = check_quote(line);
	while (a)
	{
		free(glob.herd);
		glob.herd = NULL;
		if (a == 1)
			glob.herd = ft_strdup(DQUOTE);
		else
			glob.herd = ft_strdup(QUOTE);
		str = readline(glob.herd);	
		if (!str)
		{
			if (!glob.no_init)
			{
				ft_putstr_fd("\033[4;31m bash: unexpected EOF while looking for matching `", 2);
				ft_putchar_fd(((a == 2) * '\'' + (a == 1) * '\"'), 2);
				ft_putstr_fd("'\nbash: syntax error: unexpected end of file\033[0m\n", 2);
			}
			glob.no_init = 1;
			free(line);
			free(str);
			return (NULL);
		}
		line = ft_strjoin_freed2(line, str, 0);
		a = check_quote(line);
	}
	return (line);
}
