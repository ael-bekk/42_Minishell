/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 04:04:14 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 04:04:19 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_built(char *cmd)
{
	int		i;
	char	*str[8];

	str[0] = "echo";
	str[1] = "env";
	str[2] = "cd";
	str[3] = "pwd";
	str[4] = "unset";
	str[5] = "exit";
	str[6] = "export";
	str[7] = NULL;
	i = -1;
	while (cmd && str[++i])
		if (!ft_strncmp(cmd, str[i], ft_strlen(str[0]) + 1))
			return (1);
	return (0);
}

int	exec_built(t_cmd *cmd)
{
	if (!cmd || !cmd->cmd[0])
		return (0);
	if (!ft_strncmp(cmd->cmd[0], "cd", 3))
		return (blt_cd(cmd->cmd[1]));
	if (!ft_strncmp(cmd->cmd[0], "echo", 5))
		return (blt_echo(&cmd->cmd[1], cmd->out));
	if (!ft_strncmp(cmd->cmd[0], "pwd", 4))
		return (blt_pwd(cmd->cmd[1], cmd->out));
	if (!ft_strncmp(cmd->cmd[0], "env", 4))
		return (blt_env(cmd->cmd[1], cmd->out));
	if (!ft_strncmp(cmd->cmd[0], "exit", 5))
		return (blt_exit(&cmd->cmd[1]));
	if (!ft_strncmp(cmd->cmd[0], "unset", 6))
		return (blt_unset(&cmd->cmd[1]));
	if (!ft_strncmp(cmd->cmd[0], "export", 7))
		return (blt_export(&cmd->cmd[1], &g_glob.env, cmd->out, 3)
			|| blt_export(&cmd->cmd[1], &g_glob.local, cmd->out, 2));
	return (g_glob.exit_code);
}

int	print_check_error(char *str)
{
	ft_putstr_fd("\033[4;31mError: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\033[0m\n", 2);
	g_glob.exit_code = 127;
	return (0);
}

int	check_path(char **str, t_list *path)
{
	int		i;
	char	**s_path;
	char	*p;

	i = -1;
	if (!path)
	{
		ft_putstr_fd("\033[4;31mError: PATH doesn't exist\033[0m\n", 2);
		g_glob.exit_code = 127;
		return (0);
	}
	s_path = ft_split(path->value, ':');
	while (s_path[++i])
	{
		p = ft_strjoin_freed(ft_strdup(s_path[i]), "/", 1);
		p = ft_strjoin_freed(p, *str, 1);
		if (access(p, X_OK) != -1)
		{
			free(*str);
			*str = p;
			return (1);
		}
		free(p);
	}
	return (print_check_error(*str));
}
