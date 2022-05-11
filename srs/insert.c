#include "../inc/minishell.h"

t_cmd   *creat_node(void)
{
    t_cmd *node;

    node = (t_cmd *)malloc(sizeof(t_cmd));
    node->here_doc = NULL;
    node->in_file = NULL;
    node->out_files = NULL;
    node->out_type = NULL;
    node->cmd = NULL;
    node->next = NULL;
    return (node);
}

void    add_back_node(t_cmd **head, t_cmd *new)
{
    if (!*head)
		*head = new;
	else
		ft_lstlast(*head)->next = new;
}