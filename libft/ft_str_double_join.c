#include "libft.h"

void    init_data2(char **s, int len)
{
    while (len--)
        s[len] = NULL;
}

char    **ft_str_double_join(char ***s1, char **s2, int l1, int l2)
{
    int     i;
    int     j;
    char    **new;
    
    new = (char **)malloc(sizeof(char *) * (l1 + l2 + 1));
    init_data2(new, l1 + l2 + 1);
    i = -1;
    j = 0;
    while (++i < l1 && (*s1)[i])
        new[j++] = (*s1)[i];
    i = -1;
    while (++i < l2)
    {
        new[j++] = s2[i];
        s2[i] = NULL;
    }
    free(*s1);
    *s1 = NULL;
    return (new);
}