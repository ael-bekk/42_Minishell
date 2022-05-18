#include "../inc/minishell.h"

void    ft_free_list(t_cmd **head)
{
    t_cmd *tmp;

    
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