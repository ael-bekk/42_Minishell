/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 04:26:10 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 04:26:13 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	appand_file(t_cmd *cmd, char *s)
{
	if (cmd->out != 1)
		close(cmd->out);
	if (!s || s[0] == -3)
		return (errors_return_red(&s[1], cmd));
	cmd->out = open(s, O_APPEND | O_WRONLY | O_CREAT, 0666);
	if (cmd->out == ERROR_SYS_CALL)
		return (errors_return(s));
	return (0);
}

int	out_file(t_cmd *cmd, char *s)
{
	if (cmd->out != 1)
		close(cmd->out);
	if (!s || s[0] == -3)
		return (errors_return_red(&s[1], cmd));
	cmd->out = open(s, O_TRUNC | O_WRONLY | O_CREAT, 0666);
	if (cmd->out == ERROR_SYS_CALL)
		return (errors_return(s));
	return (0);
}
