/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_or_and.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 04:21:39 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 04:21:42 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static	void	ft_norm(char *line, int *i, int *a, int *check)
{
	if (line[*i] == 34 || line[*i] == 39)
		*i += skip_qoute_inside(line + *i);
	else if (line[*i + 1] && ((line[*i] == '&' && line[*i + 1] == '&')
			|| (line[*i] == '|' && line[*i + 1] == '|')))
	{
		line[*i] = '\0';
		if ((!g_glob.exit_code && *check == 1)
			|| (g_glob.exit_code && *check == 2) || !*a)
			mini_cmd((line + *a));
		*check = (line[*i + 1] == '&') + 2 * (line[*i + 1] == '|');
		*a = ++(*i) + 1;
	}
}

void	or_and(char	*line)
{
	int	i;
	int	a;
	int	check;
	int	lent;

	a = 0;
	i = 0;
	check = 1;
	if (!line)
		return ;
	lent = ft_strlen(line);
	delete_parentheses(line);
	while (i < lent)
	{
		a = i;
		while (line[i])
		{
			ft_norm(line, &i, &a, &check);
			i++;
		}
	}
	if ((!g_glob.exit_code && check == 1) || (g_glob.exit_code && check == 2))
		mini_cmd((line + a));
	else if (!a)
		mini_cmd((line + a));
}
