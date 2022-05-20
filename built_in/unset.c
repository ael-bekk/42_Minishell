#include "../inc/minishell.h"

int is_valid_var2(char *s)
{
    int i;

    i = 0;
    if (!ft_isalpha(s[0]) && s[i] != '_')
        return (0);
    while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
        i++;
    if (!s[i])
        return (1);
    return (0);
}

void	ft_lstdel_from_list(t_list **lst, t_list *to_del)
{
    t_list *tmp;

    tmp = *lst;
    if (*lst && *lst == to_del)
    {
	    *lst = (*lst)->next;
        ft_lstdelone(tmp, free);
    }
    else if (*lst)
    {
        while (tmp->next)
        {
            if (tmp->next == to_del)
            {
                tmp->next = tmp->next->next;
                break ;
            }
            tmp = tmp->next;
        }
        ft_lstdelone(to_del, free);
    }
}

int blt_unset(char **cmd)
{
    int     i;
    int     res;
    t_list  *env;
    t_list  *tmp;

    i = -1;
    while (cmd && cmd[++i])
    {
        env = glob.env;
        res = !is_valid_var2(cmd[i]);
        while (env && !res)
        {
            if (!ft_strncmp(cmd[i], env->key, strlen(cmd[i])) && strlen(cmd[i]) == strlen(env->key))
                ft_lstdel_from_list(&glob.env, env);
            env = env->next;
        }
        if (res)
            printf("%s: export: `%s': not a valid identifier\n", glob.av[0], cmd[i]);
        glob.exit_code = glob.exit_code || res;
    }
    return (glob.exit_code);
}