/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <mounadi1337@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:22:12 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/12 18:28:19 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strdup_line(const char *s1)
{
	int		i;
	char	*copy;

	i = 0;
	while (s1[i] != '\0')
		i++;
	copy = (char *)malloc(sizeof(char) * i + 1);
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strchr_line(const char *s, int c)
{
	unsigned int	i;

	if (!s)
		return (NULL);
	i = 0;
	if (c == 0)
		return ((char *)(s + ft_strlen(s)));
	while (s[i])
		if (s[i++] == (char)c)
			return ((char *)(s + i - 1));
	return (0);
}

char	*ft_strjoin_freed(char *s1, char *s2, int type)
{
	size_t		i;
	size_t		j;
	char		*str;

	if (!s1)
		s1 = ft_strdup_line("");
	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	str = (char *)malloc(i + j + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	if (type == 0 && s1[0] != '\0')
		str[i++] = '\n';
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}
