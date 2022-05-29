/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:08:36 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/05/26 18:12:11 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	in_file(t_cmd *cmd, char *s)
{
	if (cmd->in && !glob.last_in)
		close(cmd->in);
	if (!s || s[0] == -3)
		return (errors_return_red(&s[1], cmd));
	if (!glob.last_in)
	{
		cmd->in = open(s, O_RDONLY);
		if (cmd->in == ERROR_SYS_CALL)
		{
			cmd->use = 0;
			return (errors_return(s));
		}
	}
	else if (open(s, O_RDONLY) == ERROR_SYS_CALL)
	{
		cmd->use = 0;
		return (errors_return(s));
	}
	return (0);
}

int	match_strings(char *s1, char *s2, int lent, char fin)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (!fin && !s1[i] && !s2[i] && i == lent)
		return (TRUE);
	if (fin && s1[i] == '\n' && i == lent)
		return (TRUE);
	return (FALSE);
}

void	red_here_doc(t_cmd *cmd, char *limiter, int *p)
{
	int cont;
	char *line;

	line = NULL;
	cont = FALSE;
	while (cont == FALSE)
	{
		line = readline(glob.herd);
		if (line)
			cont = match_strings(line, limiter, ft_strlen(limiter), 0);
		else
		{
			glob.no_init = 1;
			free(line);
			break;
		}
		if (!cmd->t_type)
			line = delete_quote2(expand2(line));
		if (cont == FALSE)
		{
			write(p[1], line, ft_strlen(line));
			write(p[1], "\n", 1);
		}
		free(line);
	}
}

int	here_doc(t_cmd *cmd, char *limiter)
{
	int i;
	int p[2];

	glob.p = dup(0);
	pipe(p);
	if (cmd->in)
		close(cmd->in);
	cmd->in = p[0];
	free(glob.herd);
	glob.herd = ft_strdup("");
	i = -1;
	while (++i < glob.nb_cmd - 1)
		glob.herd = ft_strjoin11(glob.herd, ft_strdup("pipe "));
	glob.herd = ft_strjoin11(glob.herd, ft_strdup("heredoc> \033[0m"));
	red_here_doc(cmd, limiter, p);
	close(p[1]);
	dup(glob.p);
	close(glob.p);
	glob.p = -1 * !glob.no_init;
	return (glob.exit_code);
}