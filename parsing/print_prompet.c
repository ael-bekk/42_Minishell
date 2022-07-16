/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompet.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 04:26:30 by amounadi          #+#    #+#             */
/*   Updated: 2022/07/16 22:11:33 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_prompet(void)
{
	t_list	*home;
	char	*pwd;

	if (g_glob.no_nl)
	{
		printf("\033[0;90m\033[0;106m%%\033[0m\n");
		g_glob.no_nl = 0;
	}
	printf("\033[1;32m");
	printf("%s\033[1;34m", (char *)find_var2("PS1", g_glob.local)->value);
	home = find_var2("HOME", g_glob.env);
	pwd = getcwd(NULL, 0);
	if (pwd && home && ft_strnstr(pwd, home->value, ft_strlen(home->value)))
		printf(" [~%s]\n", &pwd[ft_strlen(home->value)]);
	else if (pwd)
		printf(" [%s]\n", pwd);
	else
		printf(" [😵 : PWD NOT FOUND]\n");
	free(pwd);
}
