/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:07:35 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/05/29 01:24:29 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	print_export(int fd)
{
	char	**str;
	int		i;

	i = -1;
	str = list_to_str(glob.local);
	ft_sort_arry(str);
	while (str[++i])
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(str[i], fd);
		ft_putstr_fd("\n", fd);
	}
	ft_free(str);
	return (0);
}

t_list	*find_var2(char *key, t_list *env)
{
	char	*tmp;

	while (env)
	{
		if (!ft_strncmp(key, env->key, strlen(env->key) + 1))
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	is_valid_var(char *s, int type)
{
	int	i;
	int	p_m;

	i = 0;
	if (!ft_isalpha(s[0]) && s[0] != '_')
	{
		printf("%s: export: `%s': not a valid identifier\n", glob.av[0], s);
		return (0);
	}
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	if (!s[i])
		return (type);
	if (s[i] == '+' && s[i + 1] == '=')
		return (1);
	if (s[i] == '=')
		return (2);
	printf("%s: export: `", glob.av[0]);
	p_m = (s[i] == '=');
	i = 0;
	while (s[i] && ((s[i] != '=' && p_m) || !p_m))
		printf("%c", s[i++]);
	printf("': not a valid identifier\n");
	return (0);
}

void	blt_export2(char *cmd, t_list **g, int *type, int tp)
{
	t_list	*node;
	int		p;

	*type = is_valid_var(cmd, tp);
	if (*type && *type < 3)
	{
		p = equal_place(cmd);
		cmd[p - (*type == 1)] = 0;
		node = find_var2(cmd, *g);
	}
	if (!node)
		ft_lstadd_back(g, ft_lstnew(ft_strdup(cmd), ft_strdup(&cmd[p + 1])));
	else if (*type == 1 && node)
		node->value = ft_strjoin_freed(node->value, &cmd[p + 1], 1);
	else if (*type == 2 && node)
	{
		free(node->value);
		node->value = ft_strdup(&cmd[p + 1]);
	}
	if (*type && *type < 3)
		cmd[p - (*type == 1)] = '=' * (*type == 2) + '+' * (*type == 1);
}

int	blt_export(char **cmd, t_list **g, int fd, int tp)
{
	int	i;
	int	type;
	int	ret;

	i = -1;
	ret = 0;
	if (!cmd[0] && tp == 2)
		return (print_export(fd));
	while (cmd && cmd[++i])
	{
		blt_export2(cmd[i], g, &type, tp);
		ret += !type;
	}
	return (ret != 0);
}
