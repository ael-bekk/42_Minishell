/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 04:04:39 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 04:04:43 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	count_symbole(char *str)
{
	int	i;
	int	a;

	i = -1;
	a = 0;
	while (str[++i])
		if (str[i] == '>' || str[i] == '<')
			a++;
	return (a * 2);
}

void	add_space_line1(char *s, char *str, int *i, int *j)
{
	str[(*j)++] = ' ';
	str[(*j)++] = s[(*i)++];
	str[(*j)++] = s[(*i)++];
	str[(*j)++] = ' ';
}

void	add_space_line2(char *s, char *str, int *i, int *j)
{
	str[(*j)++] = ' ';
	str[(*j)++] = s[(*i)++];
	str[(*j)++] = ' ';
}

void	add_space_line3(char *s, char *str, int *i, int *j)
{
	int	type;

	type = (s[(*i)] == '\'') + 2 * (s[(*i)] == '\"');
	if (type)
		str[(*j)++] = s[(*i)++];
	while (type && s[(*i)] && ((type == 1 && s[(*i)] != '\'')
			|| (type == 2 && s[(*i)] != '\"')))
		str[(*j)++] = s[(*i)++];
	str[(*j)++] = s[(*i)++];
}

char	*separ_line(char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(ft_strlen(s) + count_symbole(s) + 1);
	while (s[i])
	{
		if (s[i + 1] && ((s[i] == '>' && s[i + 1] == '>')
				|| (s[i] == '<' && s[i + 1] == '<')))
			add_space_line1(s, str, &i, &j);
		else if (s[i] == '>' || s[i] == '<')
			add_space_line2(s, str, &i, &j);
		else
			add_space_line3(s, str, &i, &j);
	}
	free(s);
	str[j] = '\0';
	return (str);
}
