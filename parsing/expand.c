#include "../inc/minishell.h"

char *find_var(char *to_find)
{
    t_list *env;
    char *tmp;

    env = glob.env;
    while (env)
    {
        if (!ft_strncmp(to_find, env->key, strlen(env->key) + 1))
            return (ft_strdup(env->value));
        env = env->next;
    }
    return (ft_strdup(""));
}

char    *expand(char *l, char *av)
{
    char *line;
    int i;
    int left;

    left = 0;
    i = -1;
    line = NULL;
    while (l && l[++i])
    {
        if (l[i] == '\'')
            while (l[++i] && l[i] != '\'')
                ;
        if (l[i] == '$' && ft_isdigit(l[i + 1]))
        {
            line = ft_strjoin_freed2(line, ft_substr(l, left, i - left), 1);
            if (l[i + 1] == '0')
                line = ft_strjoin_freed(line, &av[2], 1);
            else
                line = ft_strjoin_freed(line, "", 1);
            left = ++i + 1;
        }
        else if (l[i] == '$' && l[i + 1] == '?')
        {
            line = ft_strjoin_freed2(line, ft_substr(l, left, i - left), 1);
            line = ft_strjoin_freed2(line, ft_itoa(glob.exit_code), 1);
            left = ++i + 1;
        }
        else if (l[i] == '$' && (l[i + 1] == '\'' || l[i + 1] == '\"' || l[i + 1] == '_' || ft_isalpha(l[i + 1])))
        {
            line = ft_strjoin_freed2(line, ft_substr(l, left, i - left), 1);
            left = ++i;
            while (l[i] && (ft_isalnum(l[i]) || l[i] == '_'))
                i++;
            line = ft_strjoin_freed2(line, find_var(ft_substr(l, left, i - left)), 1);
            left = i;
            i--;
        }
    }
    line = ft_strjoin_freed2(line, ft_substr(l, left, i - left), 1);
    free(l);
    return (line);
}
