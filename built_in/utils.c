/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 04:02:41 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 04:02:44 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	change_pwd(void)
{
	char	*e[2];

	e[0] = ft_strjoin_freed2(ft_strdup("PWD="), getcwd(NULL, 0), 1);
	e[1] = NULL;
	blt_export(e, &g_glob.env, 1, 3);
	free(e[0]);
}

void	change_old_pwd(char *s)
{
	char	*e[2];

	e[0] = ft_strjoin_freed2(ft_strdup("OLDPWD="), s, 1);
	e[1] = NULL;
	blt_export(e, &g_glob.env, 1, 3);
	free (e[0]);
}
