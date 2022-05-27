/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:47:33 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/05/27 13:52:48 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack && haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] && j + i < len
			&& haystack[i + j] == needle[j])
			j++;
		if (!needle[j])
			return (&((char *)haystack)[i]);
		i++;
	}
	return (NULL);
}
