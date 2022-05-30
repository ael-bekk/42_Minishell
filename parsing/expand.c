/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 04:19:53 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 04:19:57 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*find_var(char *key, t_list *env)
{
	char	*tmp;

	while (env)
	{
		if (!ft_strncmp(key, env->key, strlen(env->key) + 1))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

void	f1(char **line, char *l, int *ll, int *r)
{
	int		i;
	int		left;
	char	*tmp;

	left = *ll;
	i = *r;
	tmp = ft_strdup(" ");
	tmp[0] = -2;
	*line = ft_strjoin11(*line, ft_substr(l, left, i - left));
	*line = ft_strjoin11(*line, ft_strdup(tmp));
	if (l[i + 1] == '0')
		*line = ft_strjoin_freed(*line, &glob.av[0][2], 1);
	left = ++i + 1;
	*r = i;
	*ll = left;
	*line = ft_strjoin11(*line, ft_strdup(tmp));
	free(tmp);
}

void	f2(char **line, char *l, int *ll, int *r)
{
	int		i;
	int		left;
	char	*tmp;

	i = *r;
	left = *ll;
	tmp = ft_strdup(" ");
	tmp[0] = -2;
	*line = ft_strjoin11(*line, ft_substr(l, left, i - left));
	*line = ft_strjoin11(*line, ft_strdup(tmp));
	*line = ft_strjoin11(*line, ft_itoa(glob.exit_code));
	*line = ft_strjoin11(*line, ft_strdup(tmp));
	left = ++i + 1;
	*r = i;
	*ll = left;
	free(tmp);
}

void	f3(char **line, char *l, int *ll, int *r)
{
	int		i;
	int		left;
	char	*tmp;

	left = *ll;
	i = *r;
	*line = ft_strjoin11(*line, ft_substr(l, left, i - left));
	left = ++i;
	tmp = ft_strdup(" ");
	tmp[0] = -2;
	*line = ft_strjoin11(*line, ft_strdup(tmp));
	free(tmp);
	while (l[i] && (ft_isalnum(l[i]) || l[i] == '_'))
		i++;
	tmp = ft_substr(l, left, i - left);
	*line = ft_strjoin11(*line, find_var(tmp, glob.env));
	left = i;
	i--;
	*r = i;
	*ll = left;
	free(tmp);
	tmp = ft_strdup(" ");
	tmp[0] = -2;
	*line = ft_strjoin11(*line, ft_strdup(tmp));
	free(tmp);
}

char	*expand(char *l)
{
	char	*line;
	int		i;
	int		left;
	int		in_dquote;

	left = 0;
	i = -1;
	line = NULL;
	in_dquote = 0;
	while (l && l[++i])
	{
		if (l[i] == '\"')
			in_dquote = !in_dquote;
		while (l[i] == '\'' && !in_dquote && l[++i] && l[i] != '\'')
			;
		if (l[i] == '$' && ft_isdigit(l[i + 1]))
			f1(&line, l, &left, &i);
		else if (l[i] == '$' && l[i + 1] == '?')
			f2(&line, l, &left, &i);
		else if (l[i] == '$' && (((l[i + 1] == '\'' || l[i + 1] == '\"')
					&& !in_dquote) || l[i + 1] == '_' || ft_isalpha(l[i + 1])))
			f3(&line, l, &left, &i);
	}
	line = ft_strjoin11(line, ft_substr(l, left, i - left));
	free(l);
	return (line);
}
