/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 04:18:01 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 04:18:06 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	open_pipes(t_cmd *cmd)
{
	int	p[2];

	cmd->in = STDIN_FILENO;
	while (cmd->next)
	{
		if (pipe(p) == ERROR_SYS_CALL)
			return (errors_return("pipe"));
		cmd->out = p[1];
		cmd->next->in = p[0];
		cmd = cmd->next;
	}
	cmd->out = STDOUT_FILENO;
	return (0);
}

int	read_from_here_doc(t_cmd *cmd)
{
	int	i;

	while (cmd && g_glob.p == -1)
	{
		i = -1;
		while (cmd->here_doc[++i] && g_glob.p == -1)
			here_doc(cmd, cmd->here_doc[i]);
		cmd = cmd->next;
	}
	g_glob.p = -1;
	return (g_glob.exit_code);
}

int	open_files(t_cmd *cmd, int (*t[4])(t_cmd *, char *))
{
	int	i;

	while (cmd && g_glob.p == -1 && !g_glob.exit_code)
	{
		i = -1;
		while (cmd->rid[++i] && g_glob.p == -1 && !g_glob.exit_code)
			t[cmd->type[i]](cmd, cmd->rid[i]);
		cmd = cmd->next;
	}
	g_glob.exit_code = !!g_glob.exit_code;
	return (0);
}

int	define_cmd(t_cmd *cmd)
{
	int	(*t[4])(t_cmd *, char *);

	g_glob.p = -1;
	t[1] = in_file;
	t[2] = out_file;
	t[3] = appand_file;
	g_glob.exit_code = 0;
	if (open_pipes(cmd))
		return (g_glob.exit_code);
	if (read_from_here_doc(cmd))
		return (g_glob.exit_code);
	if (open_files(cmd, t))
		return (g_glob.exit_code);
	return (g_glob.exit_code);
}
