/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:07:31 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/05/29 01:32:58 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	blt_env(char *s, int fd_out)
{
	int			i;
	t_list		*lst;
	char		**str;

	str = list_to_str(glob.env);
	ft_sort_arry(str);
	if (s)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		glob.exit_code = 1;
		return (1);
	}
	i = -1;
	while (str && str[++i])
	{
		ft_putstr_fd(str[i], fd_out);
		ft_putstr_fd("\n", fd_out);
	}
	return (0);
}
