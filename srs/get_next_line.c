/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi <mounadi1337@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:27:41 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/12 18:59:12 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static	void	ft_free_line(char **str)
{
	free(*str);
	*str = NULL;
}

char	*ft_delete_line(char *stock)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
	{
		ft_free_line(&stock);
		return (NULL);
	}
	res = (char *)malloc(ft_strlen(stock) - i + 1);
	if (!res)
		return (NULL);
	i++;
	while (stock[i])
		res[j++] = stock[i++];
	res[j] = '\0';
	ft_free_line(&stock);
	return (res);
}

char	*ft_read_line(char *stock, int fd)
{
	char	*buff;
	int		check_error;

	buff = (char *)malloc(11);
	check_error = 1;
	if (!buff)
		return (NULL);
	buff[0] = '\0';
	while (!ft_strchr_line(stock, '\n') && check_error != 0)
	{
		check_error = read(fd, buff, 10);
		if (check_error == -1)
		{
			ft_free_line(&buff);
			return (NULL);
		}
		buff[check_error] = '\0';
		if (buff[0])
			stock = ft_strjoin_freed(stock, buff, 1);
	}
	ft_free_line(&buff);
	return (stock);
}

int	ft_strlen_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	static char		*stock = NULL;
	char			*line;
	int				i;

	i = 0;
	stock = ft_read_line(stock, fd);
	if (!stock)
		return (NULL);
	if (!stock[i])
	{
		ft_free_line(&stock);
		return (NULL);
	}
	line = (char *)malloc(ft_strlen_newline(stock) + 2);
	if (!line)
		return (NULL);
	i = -1;
	while (stock[++i] && stock[i] != '\n')
		line[i] = stock[i];
	line[i] = '\0';
	stock = ft_delete_line(stock);
	return (line);
}
