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

static	int check_quote(char *str)
{
	int i = 0;
	int a = 0;
	char c;
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
	line = malloc(ft_strlen(str) + 1);
	while (str && str[i])
	{
		if ((c == 0 || c == str[i]) && (str[i] == '\'' || str[i] == '\"'))
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
	line[j++] = '\0';
	free(str);
	str = NULL;
	return (line);
}

int print_quote(char *line)
{
	
	if (check_quote(line) == 1)
		ft_putstr_fd("\033[0;32mdquote> \033[0;37m", 1);
	else if (check_quote(line) == 2)
		ft_putstr_fd("\033[0;32mquote> \033[0;37m", 1);
	else
		return (0);
	return (1);
}

char *handel_quote(char *line)
{
	char *str;
	int a = 1;

	a = print_quote(line);
	while (a)
	{
		str = get_next_line(0);
		line = ft_strjoin_freed(line, str, 0);
		a = print_quote(line);
	}
	
	//line = delete_quote(line);
	return (line);
}
