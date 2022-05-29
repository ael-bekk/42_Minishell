/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:54:21 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/05/29 01:44:43 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	equal_place(char *s)
{
	int	i;

	i = -1;
	while (s && s[++i])
		if (s[i] == '=')
			return (i);
	return (i);
}

void	copy_data_env(char **ev)
{
	blt_export(ev, &glob.env, 1, 3);
	blt_export(ev, &glob.local, 1, 2);
}

char	**list_to_str(t_list *head)
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

void	ft_sort_arry(char **env)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (env && env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
