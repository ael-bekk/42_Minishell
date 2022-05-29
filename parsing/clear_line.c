/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:53:00 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/05/29 01:41:51 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	clear_line(char *inp)
{
	int		i;
	int		j;
	char	in_quote;

	i = -1;
	j = 0;
	if (!inp)
		return ;
	while (++i < ft_strlen(inp))
	{
		if (inp[i] == '\"' || inp[i] == '\'')
		{
			in_quote = inp[i];
			while (++i < ft_strlen(inp) && in_quote != inp[i])
				inp[j++] = inp[i];
		}
		else if (inp[i] != '$' || (inp[i + 1] != '\"' && inp[i + 1] != '\''))
			inp[j++] = inp[i];
	}
	inp[j] = '\0';
}
