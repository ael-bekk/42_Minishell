#include "libft.h"

char    **ft_str_double_join(char ***s1, char ***s2)
{
    int     i;
    int     l1;
    int     l2;
    char    **new;

    l1 = ft_double_strlen(*s1);
    l2 = ft_double_strlen(*s1);
    new = (char **)malloc(sizeof(char *) * (l1 + l2 + 1));
    i = -1;
    while (++i < l1)
        new[i] = (*s1)[i];
    i = -1;
    while (++i < l2)
        new[i + l1] = (*s2)[i];
    new[i + l1] = NULL;
    ft_free(*s1);
    ft_free(*s2);
    return (new);
}