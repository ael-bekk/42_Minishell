/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 03:59:02 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 21:01:42 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	handle_tilde(char *path, char *ss)
{
	t_list	*s;

	if (!path || (path[0] == '~' && !path[1]))
	{
		s = find_var2("HOME", g_glob.env);
		if (s && chdir(s->value) == -1)
		{
			printf("%s: cd: %s: %s\n", g_glob.av[0], s->value, strerror(errno));
			g_glob.exit_code = 1;
			free(ss);
			return (1);
		}
		change_old_pwd(ss);
		change_pwd();
		return (1);
	}
	return (0);
}

int	handle_minus(char *path, char *ss)
{
	t_list	*s;

	if (path[0] == '-' && !path[1])
	{
		s = find_var2("OLDPWD", g_glob.env);
		if (s && chdir(s->value) == -1)
		{
			printf("%s: cd: %s: %s\n", g_glob.av[0], s->value, strerror(errno));
			g_glob.exit_code = 1;
			free(ss);
			return (1);
		}
		else if (!s)
		{
			printf("%s: cd: OLDPWD not set\n", g_glob.av[0]);
			g_glob.exit_code = 1;
			free(ss);
			return (1);
		}
		change_old_pwd(ss);
		change_pwd();
		return (1);
	}
	return (0);
}

int	handle_dot(char *path, char *ss)
{
	char	*pwd;

	if (path[0] == '.' && !path[1])
	{
		pwd = getcwd(NULL, 0);
		if (!ft_strncmp(path, ".", 2) && !pwd)
		{
			printf("cd: error retrieving current directory: getcwd: cannot ");
			printf("access parent directories: No such file or directory\n");
			g_glob.exit_code = 0;
			free(ss);
			free(pwd);
			return (1);
		}
		else if (!pwd)
		{
			free(pwd);
			return (1);
		}
		free(pwd);
	}
	return (0);
}

int	blt_cd(char *path)
{
	char	*s;

	g_glob.exit_code = 0;
	s = getcwd(NULL, 0);
	if (handle_tilde(path, s))
		return (g_glob.exit_code);
	if (handle_minus(path, s))
		return (g_glob.exit_code);
	if (handle_dot(path, s))
		return (g_glob.exit_code);
	if (chdir(path) == -1)
	{
		printf("%s: cd: %s: %s\n", g_glob.av[0], path, strerror(errno));
		free(s);
		g_glob.exit_code = 1;
		return (1);
	}
	change_pwd();
	change_old_pwd(s);
	return (g_glob.exit_code);
}
