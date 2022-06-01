/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 04:21:15 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 04:21:19 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_list(t_cmd **head)
{
	t_cmd	*tmp;

	while (head && *head)
	{
		tmp = *head;
		ft_free(tmp->here_doc);
		ft_free(tmp->rid);
		ft_free(tmp->cmd);
		free(tmp->type);
		*head = (*head)->next;
		free(tmp);
	}
}
