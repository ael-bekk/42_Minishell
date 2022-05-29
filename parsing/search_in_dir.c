#include "../inc/minishell.h"

int	check_dir(char *path)
{
	DIR *dir;

	dir = opendir(path);
	if (!dir)
		return (0);
	closedir(dir);
	return (1);
}

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

void	search_in_dir3(char *d, char **pfix_sfix, char **new_p_s, char **new_d)
{
	*new_d = ft_strjoin_freed(ft_strdup(d), "/", 1);
	*new_d = ft_strjoin_freed(*new_d, glob.d_name, 1);
	new_p_s[0] = ft_strjoin_freed(ft_strdup(pfix_sfix[0]), glob.d_name, 1);
	new_p_s[0] = ft_strjoin_freed(new_p_s[0], "/", 1);
	new_p_s[1] = pfix_sfix[1];
}