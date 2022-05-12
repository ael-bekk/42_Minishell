#include "../inc/minishell.h"

void    ft_free(char **s)
{
    int i;

    i = -1;
    while (s && s[++i])
        free(s[i]);
    free(s);
}

void    pars(t_cmd **cmd, char **splt)
{
    int i;
    t_cmd *new;

    i = -1;
    new = creat_node();
    while (splt && splt[++i])
        printf("%s\n", splt[i]);
    add_back_node(cmd, new);
    ft_free(splt);
}

t_cmd    *parsing(char *line)
{
    char    **s;
    char    *tmp;
    t_cmd   *cmd;

    cmd = NULL;
    s = split(line, '|');
    for(int i = 0; s && s[i]; i++)
    {
        tmp = s[i];
        s[i] = separ_line(s[i]);
        free(tmp);
        pars(&cmd, split(s[i], ' '));
        //printf("%s\n", s[i]);
    }
    return (cmd);
}
