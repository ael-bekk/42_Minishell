/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 04:22:23 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 04:23:03 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_quote(char *str)
{
	int		i;
	int		a;
	char	c;

	i = 0;
	a = 0;
	if (!str)
		return (0);
	while (str[i])
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

char	*delete_quote(char *str)
{
	int	quote;
	int	in_expanded;
	int	i;
	int	j;

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
		else if ((str[i] == '\'' || str[i] == '\"' || str[i] == -2)
			&& (str[i] == quote || !quote) && !in_expanded)
			quote = str[i] * !quote;
		else
			str[j++] = str[i];
	}
	if (str)
		str[j] = '\0';
	return (str);
}

void	*quote2_error(char *line, char *str, int a)
{
	if (!g_glob.no_init)
	{
		ft_putstr_fd("\033[4;31m bash: unexpected EOF while looking for matching `", 2);
		ft_putchar_fd(((a == 2) * '\'' + (a == 1) * '\"'), 2);
		ft_putstr_fd("'\nbash: syntax error: unexpected end of file\033[0m\n", 2);
	}
	g_glob.no_init = 1;
	free(line);
	free(str);
	return (NULL);
}

char	*handel_quote(char *line)
{
	char	*str;
	int		a;

	a = 1;
	a = check_quote(line);
	while (a && !g_glob.error)
	{
		free(g_glob.herd);
		g_glob.herd = NULL;
		if (a == 1)
			g_glob.herd = ft_strdup(DQUOTE);
		else
			g_glob.herd = ft_strdup(QUOTE);
		str = readline(g_glob.herd);
		if (!str)
			return (quote2_error(line, str, a));
		line = ft_strjoin_freed2(line, str, 0);
		a = check_quote(line);
	}
	return (line);
}
