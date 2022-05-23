#include "../inc/minishell.h"

char    *expand2(char *l)
{
    char *line;
    int i;
    int left;

    left = 0;
    i = -1;
    line = NULL;
    while (l && l[++i])
    {
        if (l[i] == '$' && ft_isdigit(l[i + 1]))
            f1(&line, l, &left, &i);
        else if (l[i] == '$' && l[i + 1] == '?')
            f2(&line, l, &left, &i);
        else if (l[i] == '$' && (l[i + 1] == '_' || ft_isalpha(l[i + 1])))
            f3(&line, l, &left, &i);
    }
    line = ft_strjoin_freed2(line, ft_substr(l, left, i - left), 1);
    free(l);
    return (line);
}
