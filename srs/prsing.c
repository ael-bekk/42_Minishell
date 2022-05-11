#include "../inc/minishell.h"

void    parsing(char *line)
{
    char **s;
    
    s = split(line, '|');
    for(int i = 0; s[i]; i++)
        printf("%s\n", s[i]);
}