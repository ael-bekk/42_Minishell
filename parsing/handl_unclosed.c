/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_unclosed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 04:23:32 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 21:01:04 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*handl_unclosed(char *inp)
{
	g_glob.p = -1;
	if ((!check_pipe(inp, ft_strlen(inp)) || check_quote(inp)
			|| !check_or_and(inp) || check_or_and(inp) == -1) && !g_glob.error)
	{
		g_glob.p = dup(0);
		inp = check_full(inp);
		dup(g_glob.p);
		close(g_glob.p);
	}
	g_glob.p = -1;
	if (g_glob.error)
	{
		free(inp);
		return (NULL);
	}
	return (inp);
}
