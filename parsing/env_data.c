#include "../inc/minishell.h"

int equal_place(char *s)
{
    int i;

    i = -1;
    while (s && s[++i])
        if (s[i] == '=')
            return (i);
    return (i);
}

void    copy_data_env(char **ev)
{
    int eq_plc;
    int lent;

    lent = ft_double_strlen(ev);
    while (lent--)
    {
        eq_plc = equal_place(ev[lent]);
        
        ft_lstadd_front(&glob.env,
            ft_lstnew(ft_substr(ev[lent], 0, eq_plc),
            ft_substr(ev[lent], eq_plc + 1, ft_strlen(ev[lent]))));

        ft_lstadd_front(&glob.local,
            ft_lstnew(ft_substr(ev[lent], 0, eq_plc),
            ft_substr(ev[lent], eq_plc + 1, ft_strlen(ev[lent]))));
    }
}

char	**list_to_str(t_list *head)
{
	char **str;
	int i;

	i = 0;
	str = malloc(ft_lstsize(head) * sizeof(char *) + 1);
	while(head)
	{
		str[i] = ft_strjoin_freed(ft_strdup(head->key), "=", 1);
		str[i] = ft_strjoin_freed(str[i], head->value, 1);
		head = head->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}


void    ft_sort_arry(char **env)
{
    char *tmp;
    int i;
    int j;

    i = 0;
    while (env && env[i])
    {
        j = i + 1;
        while(env[j])
        {
            if (ft_strcmp(env[i], env[j]) > 0)
            {
                tmp = env[i];
                env[i] = env[j];
                env[j] = tmp;
            }
            j++;
        }
        i++;
    }
}