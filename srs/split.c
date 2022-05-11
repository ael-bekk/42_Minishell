#include "../libft/libft.h"

void split_f(char **s, char no_splt)
{
    int i;
    int j;

    i = -1;
    
    while (s[++i])
    {
        j = -1;
        while (s[i][++j])
            if (s[i][j] == -2)
                s[i][j] = no_splt;
    }
}

char **split(char *l, char no_splt)
{
    int i;
    int type;
    char **splt;

    i = 0;
    while (i < ft_strlen(l))
    {
        type = 0;
        if (l[i] == '\'')
            type = 1;
        if (l[i] == '\"')
            type = 2;
        if (type)
        {
            while (++i < ft_strlen(l) && ((type == 1 && l[i] != '\'') || (type == 2 && l[i] != '\"')))
                if (l[i] == no_splt)
                    l[i] = -2;
        }
        i++;
    }
    splt = ft_split(l, no_splt);
    split_f(splt, no_splt);
    return (splt);
}