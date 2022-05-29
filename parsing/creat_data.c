/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:54:16 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/05/29 04:29:19 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_cmd	*creat_node(void)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	node->use = 1;
	node->here_doc = NULL;
	node->rid = NULL;
	node->type = NULL;
	node->cmd = NULL;
	node->next = NULL;
	return (node);
}

t_cmd	*ft_nodelast(t_cmd *head)
{
	if (!head)
		return (head);
	if (!head->next)
		return (head);
	return (ft_nodelast(head->next));
}

void	add_back_node(t_cmd **head, t_cmd *new)
{
	if (!*head)
		*head = new;
	else
		ft_nodelast(*head)->next = new;
}
