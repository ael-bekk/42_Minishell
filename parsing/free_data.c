/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:58:56 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/05/29 21:04:30 by amounadi         ###   ########.fr       */
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
