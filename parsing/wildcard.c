/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:08:56 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/05/26 18:47:39 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


int	is_matching(char *dir, char *to_search)
{
	if (!*dir && !*to_search)
		return (1);
	if (!*dir && *to_search == '*')
		return (is_matching(dir, to_search + 1));
	if (!*dir || !*to_search)
		return (0);
	if (*to_search != '*' && *to_search != *dir)
		return (0);
	if (*to_search != '*' && *to_search == *dir)
		return (is_matching(dir + 1, to_search + 1));
	return (is_matching(dir + 1, to_search + 1)
		|| is_matching(dir, to_search + 1)
		|| is_matching(dir + 1, to_search));
}



int	wild2(char *ll, char **path, char **s, char **p_s_fix)
{
	int	i;

	if (ll[0] == '/')
		(*path)[0] = '/';
	if (ll[ft_strlen(ll) - 1] == '/')
		p_s_fix[1] = ft_strdup("/");
	else
		p_s_fix[1] = ft_strdup("");
	i = -1;
	while (ll[++i] == '/' || ll[i] == '.')
	{
		glob.d_name[0] = ll[i];
		p_s_fix[0] = ft_strjoin11(p_s_fix[0], ft_strdup(glob.d_name));
	}
	i = 0;
	while (!ft_strchr(s[i], '*'))
	{
		(*path) = ft_strjoin_freed((*path), "/", 1);
		(*path) = ft_strjoin_freed((*path), s[i], 1);
		i++;
	}
	return (i);
}

void	wild(char *ll)
{
	char	*path;
	char	*p_s_fix[2];
	char	c[2];
	char	**s;

	glob.line[glob.line_c] = NULL;
	if (!ft_strchr(ll, '*'))
		return (free(ll));
	c[1] = 0;
	path = ft_strdup(".");
	p_s_fix[0] = ft_strdup("");
	s = ft_split(ll, '/');
	glob.d_name = c;
	search_in_dir(path, p_s_fix, &s[wild2(ll, &path, s, p_s_fix)], 0);
	glob.d_name = NULL;
	glob.line[glob.line_c] = NULL;
	ft_sort_arry(glob.line);
	free(ll);
	free(path);
	ft_free(s);
	free(p_s_fix[0]);
	free(p_s_fix[1]);
}