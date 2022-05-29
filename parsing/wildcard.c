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

char	*change_wild(char *s)
{
	int i;
	char *new;

	i = -1;
	new = ft_strdup(s);
	while (new[++i])
		new[i] = new[i] * (new[i] != '*') -4 * (new[i] == '*');
	return (new);
}

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

int	check_dir(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (!dir)
		return (0);
	closedir(dir);
	return (1);
}

void	search_in_dir3(char *d, char **pfix_sfix, char **new_p_s, char **new_d)
{
	*new_d = ft_strjoin_freed(ft_strdup(d), "/", 1);
	*new_d = ft_strjoin_freed(*new_d, glob.d_name, 1);
	new_p_s[0] = ft_strjoin_freed(ft_strdup(pfix_sfix[0]), glob.d_name, 1);
	new_p_s[0] = ft_strjoin_freed(new_p_s[0], "/", 1);
	new_p_s[1] = pfix_sfix[1];
}

void	search_in_dir2(char *d, char **pfix_sfix, char **n_f, int l)
{
	char *new_d;
	char *new_p_s[2];

	search_in_dir3(d, pfix_sfix, new_p_s, &new_d);
	if (!n_f[l + 1] && (check_dir(new_d) || !pfix_sfix[1][0]))
	{
		if (n_f[0][0] == '.')
			pfix_sfix[0][ft_strlen(pfix_sfix[0]) - 1] = 0;
		if (n_f[0][1] == '.')
			pfix_sfix[0][ft_strlen(pfix_sfix[0]) - 1] = 0;
		glob.line[glob.line_c] = ft_strdup(pfix_sfix[0]);
		glob.line[glob.line_c] = ft_strjoin11(glob.line[glob.line_c], ft_strdup(glob.d_name));
		glob.line[glob.line_c] = ft_strjoin11(glob.line[glob.line_c], ft_strdup(pfix_sfix[1]));
		glob.line_c++;
		if (n_f[0][0] == '.')
			pfix_sfix[0][ft_strlen(pfix_sfix[0])] = '.';
		if (n_f[0][1] == '.')
			pfix_sfix[0][ft_strlen(pfix_sfix[0])] = '.';
	}
	else
		search_in_dir(new_d, new_p_s, n_f, l + 1);
	free(new_d);
	free(new_p_s[0]);
}

int	search_in_dir(char *d, char **pfix_sfix, char **n_f, int l)
{
	DIR				*dir;
	struct dirent	*p;
	char			*cng;

	dir = opendir(d);
	if (!dir)
		return (0);
	p = readdir(dir);
	while (p)
	{
		cng = change_wild(p->d_name);
		glob.d_name = p->d_name;
		if (is_matching(cng, n_f[l]) && ((p->d_name[0] != '.' && n_f[0][0] != '.') || n_f[0][0] == '.'))
			search_in_dir2(d, pfix_sfix, n_f, l);
		free(cng);
		glob.d_name = NULL;
		p = readdir(dir);
	}
	closedir(dir);
	return (0);
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
