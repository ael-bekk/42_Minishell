/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:16:46 by ael-bekk          #+#    #+#             */
/*   Updated: 2021/11/23 13:46:32 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free11(char **s)
{
	free(*s);
	*s = NULL;
	return (NULL);
}

char	*read_buff11(int fd, char **buff)
{
	int		end;
	int		bol;
	char	*res;

	bol = TRUE;
	while (bol)
	{
		res = (char *)malloc(BUFFER_SIZE + 1);
		if (!res)
			return (ft_free11(buff));
		end = read(fd, res, BUFFER_SIZE);
		if (!end || end == -1)
			return (ft_free11(&res));
		res[end] = 0;
		bol = (find_new_line11(res) == -1);
		*buff = ft_strjoin11(*buff, res);
		res = NULL;
	}
	return (*buff);
}

char	*read_line11(int fd, char **buff)
{
	int		end;
	char	*line;

	line = NULL;
	end = find_new_line11(*buff);
	if (end == -1)
	{
		read_buff11(fd, buff);
		end = find_new_line11(*buff);
	}
	if (end != -1)
	{
		line = ft_substr11(*buff, end);
		ft_new_buff11(buff, end + 1);
		return (line);
	}
	line = ft_strjoin11(line, *buff);
	if (!line)
		ft_free11(buff);
	*buff = NULL;
	return (line);
}

char	*get_next_line11(int fd)
{
	static char	*buff;
	char		*line;

	line = NULL;
	if (fd >= 0 && fd < OPEN_MAX && BUFFER_SIZE > 0)
	{
		if (!buff)
			read_buff11(fd, &buff);
		if (buff)
			line = read_line11(fd, &buff);
		if (!line)
			ft_free11(&buff);
	}
	return (line);
}
