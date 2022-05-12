#include "../inc/minishell.h"

int    pars(t_cmd **cmd, char **splt)
{
    t_cmd *new;

    new = creat_node();
    if (pars_error(splt) || !aloccate_data(new, splt))
    {
        ft_free(splt);
        return (1);
    }
    insertData(new, splt);
    add_back_node(cmd, new);
    return (0);
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
        if (pars(&cmd, split(s[i], ' ')))
        {
            ft_free_list(&cmd);
            return (NULL);
        }
        //printf("%s\n", s[i]);
    }
    return (cmd);
}
