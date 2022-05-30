/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 04:25:46 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 04:25:49 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*delete_quote2(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (str[i] != -2)
			str[j++] = str[i++];
		else
			i++;
	}
	if (str)
		str[j] = '\0';
	return (str);
}

void	insertdata_h(t_cmd *new, char **s, int *i, int *h)
{
	new->t_type = (ft_strchr(s[++(*i)], '\'') || ft_strchr(s[(*i)], '\"'));
	clear_line(s[(*i)]);
	new->here_doc[(*h)++] = delete_quote(ft_strdup(s[(*i)]));
	g_glob.last_in = 1;
}

void	insertdata_r(t_cmd *new, char **s, int *r, int *i)
{
	new->type[(*r)] = (s[(*i)][0] == '<')
		+ 2 * (s[(*i)][0] == '>' && !s[(*i)][1])
		+ 3 * (s[(*i)][0] == '>' && s[(*i)][1] == '>');
	new->rid[(*r)++] = delete_quote2(delete_quote
			(expand(ft_strdup(s[++(*i)]))));
	if (!new->rid[(*r) - 1] || !new->rid[(*r) - 1][0])
	{
		free(new->rid[(*r) - 1]);
		new->rid[(*r) - 1] = ft_strdup(" ");
		new->rid[(*r) - 1][0] = -3;
		new->rid[(*r) - 1] = ft_strjoin_freed(new->rid[(*r) - 1], s[(*i)], 1);
	}
	wild(delete_quote(change_wild2(s[(*i)])));
	if (g_glob.line_c)
	{
		free(new->rid[(*r) - 1]);
		new->rid[(*r) - 1] = NULL;
		new->rid = ft_str_double_join(&(new->rid),
				g_glob.line, g_glob.red, g_glob.line_c);
		(*r) = ft_double_strlen(new->rid);
		g_glob.line_c = 0;
	}
	g_glob.last_in = 0;
}

void	insertdata_c(t_cmd *new, char **s, int *c, int *i)
{
	new->cmd[(*c)++] = delete_quote2(delete_quote(expand(ft_strdup(s[(*i)]))));
	if (!ft_strrchr(s[(*i)], '\"') && !ft_strrchr(s[(*i)], '\'')
		&& (!new->cmd[(*c) - 1] || !new->cmd[(*c) - 1][0]))
	{
		free(new->cmd[--(*c)]);
		new->cmd[(*c)] = NULL;
	}
	wild(delete_quote(change_wild2(s[(*i)])));
	if (g_glob.line_c)
	{
		free(new->cmd[(*c) - 1]);
		new->cmd[(*c) - 1] = NULL;
		new->cmd = ft_str_double_join(&(new->cmd),
				g_glob.line, g_glob.cmd, g_glob.line_c);
		(*c) = ft_double_strlen(new->cmd);
		g_glob.line_c = 0;
	}
}

void	insertdata(t_cmd *new, char **s)
{
	int	h;
	int	r;
	int	c;
	int	i;

	h = 0;
	r = 0;
	c = 0;
	i = -1;
	while (s && s[++i])
	{
		if (s[i][0] == '<' && s[i][1] == '<')
			insertdata_h(new, s, &i, &h);
		else if ((s[i][0] == '>' || s[i][0] == '<'))
			insertdata_r(new, s, &r, &i);
		else
			insertdata_c(new, s, &c, &i);
	}
}
