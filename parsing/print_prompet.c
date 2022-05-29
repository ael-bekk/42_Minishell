/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompet.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:45:16 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/05/26 18:45:16 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_prompet()
{
	t_list	*home;
	char	*pwd;

	if (glob.no_nl)
	{
		printf("\033[0;90m\033[0;106m%%\033[0m\n");
		glob.no_nl = 0;
	}
	printf("\033[1;32m");
	printf("%s\033[1;34m", find_var2("PS1", glob.local)->value);
	home = find_var2("HOME", glob.env);
	pwd = getcwd(NULL, 0);
	if (pwd && home && ft_strnstr(pwd, home->value, ft_strlen(home->value)))
		printf(" [~%s]\n", &pwd[ft_strlen(home->value)]);
	else if (pwd)
		printf(" [%s]\n", pwd);
	else
		printf(" [😵 : PWD NOT FOUND]\n");
	free(pwd);
}