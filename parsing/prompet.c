/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 04:26:57 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 05:04:13 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*deppace_name(char *s)
{
	char	*c;
	int		l;
	int		r;

	r = 0;
	while (s && s[r] && s[r] != '>')
		r++;
	l = ++r;
	while (s && s[r] && s[r] != '<')
		r++;
	c = ft_substr(s, l, r - l);
	free(s);
	return (c);
}

int	cherch_file(void)
{
	int		fd;
	char	*env[2];
	char	*s;

	fd = open("/Library/Preferences/SystemConfiguration/preferences.plist", O_RDONLY);
	s = get_next_line11(fd);
	while (s)
	{
		if (ft_strnstr(s, "ComputerName", ft_strlen(s)))
		{
			env[0] = ft_strjoin_freed2(ft_strdup("COMPUTER="),
					deppace_name(get_next_line11(fd)), 1);
			env[1] = NULL;
			blt_export(env, &glob.local, 1, 2);
			free(env[0]);
			free(s);
			close(fd);
			return (1);
		}
		free(s);
		s = get_next_line11(fd);
	}
	free(s);
	close(fd);
	return (0);
}

void	prompet(void)
{
	t_list	*tmp;

	if (!cherch_file())
		ft_lstadd_back(&glob.local,
			ft_lstnew(ft_strdup("COMPUTER"), ft_strdup("COMPUTER")));
	if (!find_var2("USER", glob.local))
		ft_lstadd_back(&glob.local,
			ft_lstnew(ft_strdup("USER"), ft_strdup("USER")));
	tmp = find_var2("USER", glob.local);
	ft_lstadd_back(&glob.local,
		ft_lstnew(ft_strdup("PS1"),
			ft_strjoin_freed2(ft_strjoin_freed(ft_strdup(tmp->value), "@", 1),
				ft_strdup(find_var2("COMPUTER", glob.local)->value), 1)));
}
