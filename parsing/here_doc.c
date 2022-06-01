/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 04:25:14 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 04:25:26 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	in_file(t_cmd *cmd, char *s)
{
	if (cmd->in && !g_glob.last_in)
		close(cmd->in);
	if (!s || s[0] == -3)
		return (errors_return_red(&s[1], cmd));
	if (!g_glob.last_in)
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
	int		cont;
	char	*line;

	line = NULL;
	cont = FALSE;
	while (cont == FALSE)
	{
		line = readline(g_glob.herd);
		if (line)
			cont = match_strings(line, limiter, ft_strlen(limiter), 0);
		else
		{
			g_glob.no_init = 1;
			free(line);
			break ;
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
	int	i;
	int	p[2];

	g_glob.p = dup(0);
	pipe(p);
	if (cmd->in)
		close(cmd->in);
	cmd->in = p[0];
	free(g_glob.herd);
	g_glob.herd = ft_strdup("");
	i = -1;
	while (++i < g_glob.nb_cmd - 1)
		g_glob.herd = ft_strjoin11(g_glob.herd, ft_strdup("pipe "));
	g_glob.herd = ft_strjoin11(g_glob.herd, ft_strdup("heredoc> \033[0m"));
	red_here_doc(cmd, limiter, p);
	close(p[1]);
	dup(g_glob.p);
	close(g_glob.p);
	g_glob.p = -1 * !g_glob.no_init;
	return (g_glob.exit_code);
}
