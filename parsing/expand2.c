/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 01:41:40 by amounadi          #+#    #+#             */
/*   Updated: 2022/06/03 01:41:44 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_norm22(int *i, char *l, int *in_dquote)
{
	if (l[*i] == '\"')
		*in_dquote = -1 * !*in_dquote;
	if (l[*i] == '\'' && !*in_dquote)
		*in_dquote = 1;
	if (l[*i] && *in_dquote && *in_dquote != -1)
	{
		while (l[++(*i)] && l[*i] != '\'')
			;
		*in_dquote = 0;
	}
}

char	*find_var(char *key, t_list *env)
{
	while (env)
	{
		if (!ft_strncmp(key, env->key, strlen(env->key) + 1))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

char	*expand2(char *l)
{
	char	*line;
	int		i;
	int		left;

	left = 0;
	i = -1;
	line = NULL;
	while (l && l[++i])
	{
		if (l[i] == '$' && ft_isdigit(l[i + 1]))
			f1(&line, l, &left, &i);
		else if (l[i] == '$' && l[i + 1] == '?')
			f2(&line, l, &left, &i);
		else if (l[i] == '$' && (l[i + 1] == '_' || ft_isalpha(l[i + 1])))
			f3(&line, l, &left, &i);
	}
	line = ft_strjoin_freed2(line, ft_substr(l, left, i - left), 1);
	free(l);
	return (line);
}
