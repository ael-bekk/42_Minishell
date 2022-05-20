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
            new->here_doc[h++] = delete_quote(ft_strdup(s[++i]));
        else if ((s[i][0] == '>' || s[i][0] == '<'))
        {
            new->type[r] = (s[i][0] == '<')
                + 2 * (s[i][0] == '>' && !s[i][1])
                + 3 * (s[i][0] == '>' && s[i][1] == '>');
            new->rid[r++] = expand(ft_strdup(s[++i]));
            if (!new->rid[r - 1] || !new->rid[r - 1][0])
            {
                printf("%s: %s: ambiguous redirect\n", &glob.av[0][2], s[i]);
                new->use = 0;
            }
            else
                new->rid[r - 1] = delete_quote(new->rid[r - 1]);
        }
        else
            new->cmd[c++] = delete_quote(expand(ft_strdup(s[i])));
    }
}