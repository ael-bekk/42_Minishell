/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 04:04:56 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 04:15:21 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_data(char **s, int len)
{
	s[len] = NULL;
	while (len--)
		s[len] = NULL;
}

int	allocatedata(t_cmd *cmd, int h_doc, int red, int cmnd)
{
	cmd->here_doc = (char **)malloc(sizeof(char *) * (h_doc + 1));
	cmd->rid = (char **)malloc(sizeof(char *) * (red + 1));
	cmd->type = (int *)malloc(sizeof(int) * (red + 1));
	cmd->cmd = (char **)malloc(sizeof(char *) * (cmnd + 1));
	if (!cmd->here_doc || !cmd->rid || !cmd->cmd || !cmd->type)
		return (0);
	init_data(cmd->here_doc, h_doc);
	init_data(cmd->rid, red);
	init_data(cmd->cmd, cmnd);
	g_glob.cmd = cmnd;
	g_glob.red = red;
	g_glob.last_in = 0;
	return (1);
}

int	aloccate_data(t_cmd *cmd, char **s)
{
	int	h_doc;
	int	red;
	int	cmnd;
	int	i;

	h_doc = 0;
	red = 0;
	cmnd = 0;
	i = -1;
	while (s && s[++i])
	{
		red += ((s[i][0] == '>' && s[i][1] == '>')
				|| (s[i][0] == '<' && !s[i][1]) || s[i][0] == '>');
		h_doc += (s[i][0] == '<' && s[i][1] == '<');
		if (s[i][0] == '>' || s[i][0] == '<')
			i++;
		else
			cmnd++;
	}
	if (!cmnd)
		cmd->use = 0;
	return (allocatedata(cmd, h_doc, red, cmnd));
}
