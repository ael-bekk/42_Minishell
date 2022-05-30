/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_multi_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 04:20:52 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 04:20:56 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_line_or_and(char *str)
{
	char	c;

	while (*str && (*str == ' ' || *str == '\n'))
		str++;
	if (*str && (*str == '|' || *str == '&'))
	{
		c = *str;
		str++;
		while (*str && (*str == ' ' || *str == '\n'))
			str++;
		if (!*str || *str == '&' || *str == '|')
		{
			p_error(c);
			g_glob.error = 1;
			return (0);
		}
	}
	return (1);
}

int	check_line_pipe(char *str)
{
	char	c;

	while (*str && (*str == ' ' || *str == '\n'))
		str++;
	if (*str && (*str == '|' || *str == '&'))
	{
		c = *str;
		str++;
		while (*str && (*str == ' ' || *str == '\n'))
			str++;
		if (!*str)
		{
			p_error(c);
			g_glob.error = 1;
			return (0);
		}
	}
	return (1);
}
