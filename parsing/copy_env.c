#include "../inc/minishell.h"

char    **copy_data(char    **s)
{
    int i;
    int lent;
    char **data;

    lent = 0;
    while (s && s[lent])
        lent++;
    data = (char **)malloc(sizeof(char *) * (lent + 2));
    if (!data)
    {
        printf("Error: Couldn't allocate memory'\n");
        exit(errno);
    }
    
}