/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:47:31 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/05/29 02:44:34 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	split_f(char **s, char no_splt)
{
	int	i;
	int	j;

	i = -1;
	while (s[++i])
	{
		j = -1;
		while (s[i][++j])
			if (s[i][j] == -2)
				s[i][j] = no_splt;
	}
}

char	**split(char *l, char no_splt)
{
	int		i;
	int		type;
	char	**splt;

	i = -1;
	while (++i < ft_strlen(l))
	{
		type = (l[i] == '\'') + 2 * (l[i] == '\"');
		while (type && ++i < ft_strlen(l)
			&& ((type == 1 && l[i] != '\'') || (type == 2 && l[i] != '\"')))
			if (l[i] == no_splt)
				l[i] = -2;
	}
	splt = ft_split(l, no_splt);
	split_f(splt, no_splt);
	return (splt);
}
