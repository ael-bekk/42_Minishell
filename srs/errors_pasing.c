#include "../inc/minishell.h"

char *new_one(char *s)
{
    int i;
    int j;
    char *new;

    new = malloc(strlen(s) + -1);
    i = 0;
    j = 0;
    while(s[++i] && s[i + 1])
        new[j++] = s[i];
    new[j] = '\0';
    free(s);
    return (new);
}

int    pars_error(char **s)
{
    int i;

    i = -1;
    while (s[++i])
    {
        if (!s[i + 1] && (s[i][0] == '>' || s[i][0] == '<'))
        {
            printf("minishell: parse error near `%s'\n", s[i]);
            return (1);
        }
        if ((s[i][0] == '>' || s[i][0] == '<') && (s[i + 1][0] == '>' || s[i + 1][0] == '<'))
        {
            printf("minishell: parse error near `%s'\n", s[i]);
            return (1);
        }
        if ((s[i][0] == '\'' || s[i][0] == '\"'))
            s[i] = new_one(s[i]);
    }
    return (0);
}