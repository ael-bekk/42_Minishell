#include "../inc/minishell.h"

void    insertData(t_cmd *new, char **s)
{
    int h;
    int r;
    int c;
    int i;

    h = 0;
    r = 0;
    c = 0;
    i = -1;
    while (s && s[++i])
    {
        if (s[i][0] == '<' && s[i][1] == '<')
            new->here_doc[h++] = ft_strdup(s[++i]);
        else if ((s[i][0] == '>' || s[i][0] == '<'))
        {
            new->type[r] = (s[i][0] == '<')
                + 2 * (s[i][0] == '>' && !s[i][1])
                + 3 * (s[i][0] == '>' && s[i][1] == '>');
            new->rid[r++] = ft_strdup(s[++i]);
        }
        else
            new->cmd[c++] = ft_strdup(s[i]);
    }
}