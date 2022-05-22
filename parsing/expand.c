#include "../inc/minishell.h"

char *find_var(char *key, t_list *env)
{
    char *tmp;

    while (env)
    {
        if (!ft_strncmp(key, env->key, strlen(env->key) + 1))
            return (ft_strdup(env->value));
        env = env->next;
    }
    return (ft_strdup(""));
}

void    f1(char **line, char *l, int *ll, int *r)
{
    int i;
    int left;
    char    *tmp;

    left = *ll;
    i = *r;
    tmp = ft_strdup(" ");
    tmp[0] = -2;
    *line = ft_strjoin_freed2(*line, ft_strdup(tmp), 1);
    *line = ft_strjoin_freed2(*line, ft_substr(l, left, i - left), 1);
    if (l[i + 1] == '0')
        *line = ft_strjoin_freed(*line, &glob.av[0][2], 1);
    else
        *line = ft_strjoin_freed(*line, "", 1);
    left = ++i + 1;
    *r = i;
    *ll = left;
    *line = ft_strjoin_freed2(*line, ft_strdup(tmp), 1);
    free(tmp);
}

// void    f1()
// {

// }

void    f3(char **line, char *l, int *ll, int *r)
{
    int     i;
    char    *tmp;
    int left;

    left = *ll;
    i = *r;

    *line = ft_strjoin_freed2(*line, ft_substr(l, left, i - left), 1);
    left = ++i;
    tmp = ft_strdup(" ");
    tmp[0] = -2;
    *line = ft_strjoin_freed2(*line, ft_strdup(tmp), 1);
    free(tmp);
    while (l[i] && (ft_isalnum(l[i]) || l[i] == '_'))
        i++;
    tmp = ft_substr(l, left, i - left);
    *line = ft_strjoin_freed2(*line, find_var(tmp, glob.env), 1);
    left = i;
    i--;
    *r = i;
    *ll = left;

    tmp = ft_strdup(" ");
    tmp[0] = -2;
    *line = ft_strjoin_freed2(*line, ft_strdup(tmp), 1);
    free(tmp);
}

char    *expand(char *l)
{
    char *line;
    int i;
    int left;
    int in_dquote = 0;

    left = 0;
    i = -1;
    line = NULL;
    while (l && l[++i])
    {
        if (l[i] == '\"')
            in_dquote = !in_dquote;
        if (l[i] == '\'' && !in_dquote)
            while (l[++i] && l[i] != '\'')
                ;
        if (l[i] == '$' && ft_isdigit(l[i + 1]))
            f1(&line, l, &left, &i);
        else if (l[i] == '$' && l[i + 1] == '?')
        {
            line = ft_strjoin_freed2(line, ft_substr(l, left, i - left), 1);
            line = ft_strjoin_freed2(line, ft_itoa(glob.exit_code), 1);
            left = ++i + 1;
        }
        else if (l[i] == '$' && (l[i + 1] == '\'' || l[i + 1] == '\"' || l[i + 1] == '_' || ft_isalpha(l[i + 1])))
            f3(&line, l, &left, &i);
    }
    line = ft_strjoin_freed2(line, ft_substr(l, left, i - left), 1);
    free(l);
    return (line);
}
