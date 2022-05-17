/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:44:58 by ael-bekk          #+#    #+#             */
/*   Updated: 2021/11/23 13:50:13 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find_new_line11(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == '\n')
			return (i);
	return (-1);
}

char	*ft_strjoin11(char *s1, char *s2)
{
	int		i;
	int		l1;
	int		l2;
	char	*res;

	l1 = 0;
	l2 = 0;
	while (s1 && s1[l1])
		l1++;
	while (s2 && s2[l2])
		l2++;
	if (!(l1 + l2))
		return (NULL);
	res = (char *)malloc(l1 + l2 + 1);
	if (!res)
		return (ft_free11(&s1));
	i = -1;
	while (++i < l1)
		res[i] = s1[i];
	i = -1;
	while (++i < l2)
		res[i + l1] = s2[i];
	res[l1 + l2] = 0;
	(ft_free11(&s1) || ft_free11(&s2));
	return (res);
}

char	*ft_substr11(char *s, int end)
{
	char	*sub;
	int		i;

	if (!s[0])
		return (ft_free11(&s));
	i = -1;
	sub = (char *)malloc(end + 2);
	if (!sub)
		return (ft_free11(&s));
	while (++i <= end)
		sub[i] = s[i];
	sub[end + 1] = 0;
	return (sub);
}

void	ft_new_buff11(char **buff, int start)
{
	char	*new;
	int		end;

	end = 0;
	while ((*buff)[end + start])
		end++;
	if (!end)
	{
		ft_free11(buff);
		return ;
	}
	new = ft_substr11((*buff) + start, end - 1);
	ft_free11(buff);
	*buff = new;
}
