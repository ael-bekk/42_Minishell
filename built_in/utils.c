/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:49:20 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/05/26 18:49:58 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	change_pwd()
{
	char	*e[2];

	e[0] = ft_strjoin_freed2(ft_strdup("PWD="), getcwd(NULL, 0), 1);
	e[1] = NULL;
	blt_export(e, &glob.env, 1, 3);
	free(e[0]);
}

void	change_old_pwd(char *s)
{
	char	*e[2];

	e[0] = ft_strjoin_freed2(ft_strdup("OLDPWD="), s, 1);
	e[1] = NULL;
	blt_export(e, &glob.env, 1, 3);
	free(e[0]);
}