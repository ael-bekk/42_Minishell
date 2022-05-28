/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:52:09 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/05/27 15:03:44 by ael-bekk         ###   ########.fr       */
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
	glob.pid_cmd = fork();
	if (glob.pid_cmd == 0)
	{
		glob.pid = 1;
		dup2(cmd->in, 0);
		dup2(cmd->out, 1);
		close_all(cmd2);
		if (ft_strchr(cmd->cmd[0], '/')
			|| check_path(&cmd->cmd[0], find_var2("PATH", glob.env)))
		{
			if (execve(cmd->cmd[0], cmd->cmd, glob.exec_env) == -1)
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
			glob.exit_code = 127;
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
	int	old_exit_code;

	glob.p = -2;
	up_to = 0;
	ft_free(glob.exec_env);
	glob.exec_env = list_to_str(glob.env);
	if (glob.nb_cmd == 1 && cmd->use && check_built(cmd->cmd[0]))
		glob.exit_code = exec_built(cmd);
	else
		up_to = exec_cmds(cmd, cmd);
	close_all(cmd);
	if (up_to)
	{
		waitpid(glob.pid_cmd, &up_to, 0);
		if (!glob.exit_code)
			glob.exit_code = up_to / 256;
		up_to = !glob.exit_code;
	}
	while (wait(NULL) != -1)
		;
	glob.p = -1;
	return (((glob.exit_code / 256) * up_to) + (glob.exit_code * !up_to));
}
