/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 04:02:25 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 04:02:31 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_valid_var2(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[0]) && s[i] != '_')
		return (0);
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	if (!s[i])
		return (1);
	return (0);
}

void	ft_lstdel_from_list(t_list **lst, t_list *to_del)
{
	t_list	*tmp;

	tmp = *lst;
	if (*lst && *lst == to_del)
	{
		*lst = (*lst)->next;
		ft_lstdelone(tmp, free);
	}
	else if (*lst)
	{
		while (tmp->next)
		{
			if (tmp->next == to_del)
			{
				tmp->next = tmp->next->next;
				break ;
			}
			tmp = tmp->next;
		}
		ft_lstdelone(to_del, free);
	}
}

void	blt_unset2(char *cmd, int *res)
{
	t_list	*env;

	env = g_glob.env;
	*res = !is_valid_var2(cmd);
	while (env && !*res)
	{
		if (!ft_strncmp(cmd, env->key, ft_strlen(cmd))
			&& ft_strlen(cmd) == ft_strlen(env->key))
		{
			ft_lstdel_from_list(&g_glob.env, env);
			return ;
		}
		env = env->next;
	}
	env = g_glob.local;
	while (env && !*res)
	{
		if (!ft_strncmp(cmd, env->key, ft_strlen(cmd))
			&& ft_strlen(cmd) == ft_strlen(env->key))
		{
			ft_lstdel_from_list(&g_glob.local, env);
			return ;
		}
		env = env->next;
	}
}

int	blt_unset(char **cmd)
{
	int		i;
	int		res;

	i = -1;
	while (cmd && cmd[++i])
	{
		blt_unset2(cmd[i], &res);
		if (res)
			printf("%s: export: `%s': not a valid identifier\n",
				g_glob.av[0], cmd[i]);
		if (g_glob.exit_code)
			g_glob.exit_code = g_glob.exit_code;
		else
			g_glob.exit_code = res;
	}
	return (g_glob.exit_code);
}
