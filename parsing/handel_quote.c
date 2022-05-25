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
	int	quote;
	int	in_expanded;
	int i;
	int j;

	i = -1;
	j = 0;
	quote = 0;
	in_expanded = 0;
	while (str && str[++i])
	{
		if (str[i] == -2)
		{
			in_expanded = !in_expanded;
			str[j++] = str[i];
		}
		else if ((str[i] == '\'' || str[i] == '\"' || str[i] == -2) && (str[i] == quote || !quote) && !in_expanded)
			quote = str[i] * !quote;
		else
			str[j++] = str[i];
	}
	if (str)
		str[j] = '\0';	
	return (str);
}

char *handel_quote(char *line)
{
	char *str;
	int a = 1;

	a = check_quote(line);
	while (a && !glob.error)
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
