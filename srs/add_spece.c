/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spece.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 23:00:37 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/11 23:51:52 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
static	int	count_symbole(char *str)
{
	int i;
	int a;

	i = -1;
	a = 0;
	while(str[++i])
		if (str[i] == '>' || str[i] == '<')
			a++;
	return (a * 2);
}

char *separ_line(char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(ft_strlen(s) + count_symbole(s) + 1);
	while(s[i])
	{
		if((s[i] == '>' && s[i+1] == '>') || (s[i] == '<' && s[i+1] == '<'))
		{
			str[j++] = ' ';
			str[j++] = s[i++];
			str[j++] = s[i++];
			str[j++] = ' ';
		}
		else if(s[i] == '>' || s[i] == '<')
		{
			str[j++] = ' ';
			str[j++] = s[i++];
			str[j++] = ' ';
		}
		else if(s[i] == '\'' || )
			str[j++] = s[i++];
	}
	str[j] = '\0';
	return (str);
}
