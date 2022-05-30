/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_parentheses.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 05:18:10 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 05:18:11 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	delete_parentheses(char *str)
{
	while (*str)
	{
		if (*str == 34 || *str == 39)
			str = skip_qoute(str);
		if (*str == 40 || *str == 41)
			*str = ' ';
		str++;
	}
}

char	*skip_qoute(char *str)
{
	if (*str == '"')
	{
		str++;
		while (*str && *str != '"')
			str++;
		return (++str);
	}
	else
	{
		str++;
		while (*str && *str != '\'')
			str++;
		return (++str);
	}
}

int	check_error_parentheses(int a)
{
	if (a > 0)
		p_error('(');
	else if (a < 0)
		p_error(')');
	g_glob.error = !!a;
	return (a);
}

char	*valid_parentheses2(char *s, int *a, int *i, int *y)
{
	(*a)++;
	*y = (*i)++;
	while (*(++s) && (*s == ' ' || *s == '|' || *s == '&') && (i++))
	{
		if (*s == '|' || *s == '&')
		{
			p_error (*s);
			g_glob.error = 1;
			return (0);
		}
		(*y)++;
	}
	return (s);
}

int	valid_parentheses(char *s)
{
	int		i;
	int		a;
	int		y;

	a = 0;
	i = 0;
	y = 0;
	while (*s && a >= 0)
	{
		if (*s == '\'' || *s == '\"')
			s = skip_qoute(s);
		else if (*s == '(')
			s = valid_parentheses2(s, &a, &i, &y);
		else if (*s == ')' && y + 1 != i && ++i && s++)
			a--;
		else if (++i && s++)
			;
	}
	return (check_error_parentheses(a));
}
