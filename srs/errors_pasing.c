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

int    errors_print(char *s)
{
    if (s)
        printf("minishell: parse error near `%s'\n", s);
    else
        printf("minishell: parse error near `newline'\n");
    return (1);
}

int    pars_error(char **s)
{
    int i;

    i = -1;
    while (s[++i])
    {
        if (!s[i + 1] && (s[i][0] == '>' || s[i][0] == '<'))
            return (errors_print(s[i + 1]));
        else if ((s[i][0] == '>' || s[i][0] == '<') && (s[i + 1][0] == '>' || s[i + 1][0] == '<'))
            return (errors_print(s[i + 1]));
        else
            s[i] = delete_quote(s[i]);
    }
    return (0);
}