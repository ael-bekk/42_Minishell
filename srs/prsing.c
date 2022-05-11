#include "../inc/minishell.h"

void    parsing(char *line)
{
    char **s;
    char *tmp;
    s = split(line, '|');
    
    for(int i = 0; s[i]; i++)
        tmp = s[i],
        s[i] = separ_line(s[i]),
        free(tmp),
        printf("%s\n", s[i]);
    
}