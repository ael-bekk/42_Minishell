/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_unclosed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 04:23:32 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 04:23:35 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*handl_unclosed(char *inp)
{
	int	i;

	glob.p = -1;
	if ((!check_pipe(inp, ft_strlen(inp)) || check_quote(inp)
			|| !check_or_and(inp) || check_or_and(inp) == -1) && !glob.error)
	{
		glob.p = dup(0);
		inp = check_full(inp);
		dup(glob.p);
		close(glob.p);
	}
	glob.p = -1;
	if (glob.error)
	{
		free(inp);
		return (NULL);
	}
	return (inp);
}
