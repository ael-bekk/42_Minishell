/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prsing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 05:05:26 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 05:05:29 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	pars(t_cmd **cmd, char **splt)
{
	t_cmd	*new;

	new = creat_node();
	if (pars_error(splt) || !aloccate_data(new, splt))
	{
		ft_free(splt);
		return (1);
	}
	insertdata(new, splt);
	add_back_node(cmd, new);
	g_glob.nb_cmd++;
	ft_free(splt);
	return (0);
}

t_cmd	*parsing(char *line)
{
	int		i;
	char	**s;
	t_cmd	*cmd;

	cmd = NULL;
	if (!line)
		return (NULL);
	i = -1;
	s = split(line, '|');
	while (s && s[++i])
	{
		s[i] = separ_line(s[i]);
		if (pars(&cmd, split(s[i], ' ')))
		{
			ft_free_list(&cmd);
			ft_free(s);
			g_glob.exit_code = 258;
			return (NULL);
		}
	}
	ft_free(s);
	return (cmd);
}
