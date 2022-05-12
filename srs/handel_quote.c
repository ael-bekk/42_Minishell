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
static	char *delete_quote(char *str)
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
	while (str[i])
	{
		if ((c == 0 || c == str[i]) && (str[i] == '\'' || str[i] == '\"'))
		{
			c = str[i++];
			a++;
			if (a == 2)
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

char *handel_quote(void)
{
	char *str;
	int a = 1;
	char *line;
	int check;

	check = 0;
	while (a)
	{
		str = get_next_line(0);
		line = ft_strjoin_freed(line, str, 0);
		if (check_quote(line) == 1)
			write(1,"dquote> ",ft_strlen("dquote> "));
		else if (check_quote(line) == 2)
			write(1,"quote> ",ft_strlen("quote> "));
		else
			a = 0;
	}
	line = delete_quote(line);
	return (line);
}
