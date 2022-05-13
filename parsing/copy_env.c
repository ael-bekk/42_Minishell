#include "../inc/minishell.h"

char    **copy_data(char **s, int plus)
{
    int i;
    int lent;
    char **data;

    lent = 0;
    while (s && s[lent])
        lent++;
    data = (char **)malloc(sizeof(char *) * (lent + 1 + plus));
    if (!data)
    {
        printf("Error: Couldn't allocate memory'\n");
        exit(errno);
    }
    i = -1;
    while (s && s[++i])
        data[i] = ft_strdup(s[i]);
    data[i] = NULL;
    return (data);
}