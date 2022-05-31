/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 00:52:13 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/31 00:52:15 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_all(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->in)
			close(cmd->in);
		if (cmd->out != 1)
			close(cmd->out);
		cmd = cmd->next;
	}
}

void	exec_cmd(t_cmd *cmd, t_cmd *cmd2)
{
	g_glob.pid_cmd = fork();
	if (g_glob.pid_cmd == 0)
	{
		g_glob.pid = 1;
		dup2(cmd->in, 0);
		dup2(cmd->out, 1);
		close_all(cmd2);
		if (ft_strchr(cmd->cmd[0], '/')
			|| check_path(&cmd->cmd[0], find_var2("PATH", g_glob.env)))
		{
			if (execve(cmd->cmd[0], cmd->cmd, g_glob.exec_env) == -1)
				exit(errors_return(cmd->cmd[0]));
		}
		else
			exit (127);
	}
}

int	exec_cmds(t_cmd *cmd, t_cmd *cmd2)
{
	int	up_to;

	up_to = 1;
	while (cmd)
	{
		if (cmd->use && cmd->cmd[0] && cmd->cmd[0][0])
			exec_cmd(cmd, cmd2);
		else if (cmd->use && cmd->cmd[0] && !cmd->cmd[0][0])
		{
			ft_putstr_fd("\033[4;31mError: : command not found\033[0m\n", 2);
			g_glob.exit_code = 127;
		}
		if (!cmd->next && !cmd->use)
			up_to = 0;
		cmd = cmd->next;
	}
	return (up_to);
}

int	execution(t_cmd *cmd)
{
	int	up_to;

	g_glob.p = -2;
	up_to = 0;
	ft_free(g_glob.exec_env);
	g_glob.exec_env = list_to_str(g_glob.env);
	if (g_glob.nb_cmd == 1 && cmd->use && check_built(cmd->cmd[0]))
		g_glob.exit_code = exec_built(cmd);
	else
		up_to = exec_cmds(cmd, cmd);
	close_all(cmd);
	if (up_to)
	{
		waitpid(g_glob.pid_cmd, &up_to, 0);
		if (!g_glob.exit_code)
			g_glob.exit_code = up_to / 256;
		up_to = !g_glob.exit_code;
	}
	while (wait(NULL) != -1)
		;
	g_glob.p = -1;
	return (((g_glob.exit_code / 256) * up_to) + (g_glob.exit_code * !up_to));
}
