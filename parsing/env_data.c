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
            ft_lstnew(ft_substr(ev[lent], 0, eq_plc - 1), 
            ft_substr(ev[lent], eq_plc + 1, ft_strlen(ev[lent]))));
    }
}