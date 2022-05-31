/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 04:24:36 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 04:24:38 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	skip_qoute_inside(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '"')
	{
		i++;
		while (str[i] && str[i] != '"')
			i++;
		return (i);
	}
	else
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		return (i);
	}
}

int	check_pipe(char *str, int len)
{
	int	i;
	int	a;

	i = -1;
	a = 1;
	check_space(str);
	while (str && ++i < len)
	{
		if (str[i] == '&' && !check_space_and(str + i))
			return (0);
		if (str[i] == '\'' || str[i] == '"')
			i += skip_qoute_inside(str + i);
		else if (str[i] == '|' && a--)
		{
			if (!check_spece_pipe(str + i))
				return (0);
			if ((str[i + 1] && str[i + 1] == '|')
				|| (str[i - 1] && str[i - 1] == '|'))
				a = 1;
		}
		else if (str[i] != ' ' && str[i] != '\n')
			a = 1;
	}
	return (a);
}

char	*handler_pipe(char *line)
{
	char	*str;
	int		a;

	a = !check_pipe(line, ft_strlen(line));
	free(g_glob.herd);
	g_glob.herd = ft_strdup("\033[0;32mpipe> \033[0;37m");
	while (a && !g_glob.error)
	{
		str = readline(g_glob.herd);
		if (!str)
		{
			if (!g_glob.no_init)
				ft_putstr_fd(SYNTAX_ERROR, 2);
			g_glob.no_init = 1;
			free(line);
			free(str);
			return (NULL);
		}
		if (!check_line_pipe(str))
			return (NULL);
		line = ft_strjoin_freed2(line, str, 1);
		a = !check_pipe(line, ft_strlen(line));
	}
	return (line);
}

char	*check_full(char *line)
{
	int	v;
	int	a;

	if (!line)
		return (NULL);
	v = (!check_pipe(line, ft_strlen(line)) || check_quote(line));
	if (!v)
		a = check_or_and(line);
	while (v || a == -1 || a == 0)
	{
		line = handel_quote(line);
		line = handler_pipe(line);
		line = handler_or_and(line);
		v = (!check_pipe(line, ft_strlen(line)) || check_quote(line));
		if (!v)
			a = check_or_and(line);
		if (g_glob.error)
		{
			free(line);
			return (NULL);
		}
	}
	return (line);
}
