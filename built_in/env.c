/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 04:01:10 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 20:57:20 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**env_to_str(t_list *head)
{
	char	**str;
	int		i;

	i = 0;
	str = malloc(ft_lstsize(head) * sizeof(char *) + 1);
	while (head)
	{
		str[i] = ft_strjoin_freed(ft_strdup(head->key), "=", 1);
		str[i] = ft_strjoin_freed(str[i], head->value, 1);
		head = head->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}

int	blt_env(char *s, int fd_out)
{
	int			i;
	char		**str;

	str = env_to_str(g_glob.env);
	if (s)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_glob.exit_code = 1;
		ft_free(str);
		return (1);
	}
	i = -1;
	while (str && str[++i])
	{
		ft_putstr_fd(str[i], fd_out);
		ft_putstr_fd("\n", fd_out);
	}
	ft_free(str);
	return (0);
}
