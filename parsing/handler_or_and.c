/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_or_and.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 04:24:07 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/31 00:49:49 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static	int	check_or_and_plus(char *s, int *i, int *a)
{
	if (*a == 1 && s[*i + 1] && ((s[*i] == '|'
				&& s[*i + 1] == '|') || (s[*i] == '&' && s[*i + 1] == '&')))
	{
		*a = -1;
		if (s[*i] == '&')
			(*a) = 0;
		if (s[*i + 1] && ((s[*i + 1] == '|' && *a == -1)
				|| (s[*i + 1] == '&' && *a == 0)))
			(*i)++;
		if (s[*i + 1] && ((s[*i] == '|' || s[*i] == '&')
				&& (s[*i + 1] == '|' || s[*i + 1] == ')' || s[*i + 1] == '(' )))
			return (0);
	}
	else if ((s[*i + 1] && s[*i] == '&' && s[*i + 1] != '&')
		|| (s[*i] == '&' && !s[*i + 1]))
		return (0);
	else if (s[*i] != ' ' && s[*i] != '\n')
		*a = 1;
	return (1);
}

int	check_or_and(char *str)
{
	int	i;
	int	a;

	i = -1;
	a = 1;
	if (!str)
		return (1);
	while (str[++i] && !g_glob.error)
	{
		if (str[i] == '\'' || str[i] == '"')
			i += skip_qoute_inside(str + i);
		else if (!check_or_and_plus(str, &i, &a))
		{
			p_error(str[i]);
			g_glob.error = 1;
			return (0);
		}
	}
	return (a);
}

static char	*ft_norm(char **line, char **str, int *a)
{
	if (!check_line_or_and(*str))
		return (NULL);
	*line = ft_strjoin_freed2(*line, *str, 1);
	*a = check_or_and(*line);
	if (*a == 0 || *a == -1)
		free(g_glob.herd);
	if (*a == 0)
		g_glob.herd = ft_strdup("cmdand> \033[0;37m");
	else if (*a == -1)
		g_glob.herd = ft_strdup("cmdor> \033[0;37m");
	return (*line);
}

static void	ft_norm2(char *line, int *a)
{
	*a = check_or_and(line);
	free(g_glob.herd);
	g_glob.herd = NULL;
	if (*a == 0)
		g_glob.herd = ft_strdup("cmdand> \033[0;37m");
	else if (*a == -1)
		g_glob.herd = ft_strdup("cmdor> \033[0;37m");
}

char	*handler_or_and(char *line)
{
	char	*str;
	int		a;

	if (!line || !line[0])
		return (NULL);
	ft_norm2(line, &a);
	while ((a == -1 || a == 0) && !g_glob.error)
	{
		str = readline(g_glob.herd);
		if (!str)
		{
			if (!g_glob.no_init)
			{
				ft_putstr_fd("\033[4;31m Minishell: syntax error", 2);
				ft_putstr_fd(": unexpected end of file\n\033[0m", 2);
			}
			g_glob.no_init = 1;
			free(line);
			free(str);
			return (NULL);
		}
		if (!ft_norm(&line, &str, &a))
			return (NULL);
	}
	return (line);
}
