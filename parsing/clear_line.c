#include "../inc/minishell.h"

void    clear_line(char *inp)
{
    int i;
    int j;
    int in_dquote;

    in_dquote = 0;
    i = -1;
    j = 0;
    if (!inp)
        return ;
    while (inp[++i])
    {
        if (inp[i] == '\"')
            in_dquote = !in_dquote;
        if (inp[i] != '$' || (inp[i + 1] != '\"' && inp[i + 1] != '\'') || in_dquote)
            inp[j++] = inp[i];
    }
    inp[j] = '\0';
}