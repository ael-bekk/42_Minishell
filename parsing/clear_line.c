#include "../inc/minishell.h"

void    clear_line(char *inp)
{
    int i;
    int j;

    i = -1;
    j = 0;
    if (!inp)
        return ;
    while (inp[++i])
        if (inp[i] != '$' || (inp[i + 1] != '\"' && inp[i + 1] != '\''))
            inp[j++] = inp[i];
    inp[j] = '\0';
}