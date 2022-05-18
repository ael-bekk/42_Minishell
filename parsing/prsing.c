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
    ft_free(splt);
    return (0);
}

t_cmd    *parsing(char *line)
{
    char    **s;
    t_cmd   *cmd;

    cmd = NULL;
	if (!line)
		return (NULL);
    s = split(line, '|');
    for(int i = 0; s && s[i]; i++)
    {
        s[i] = separ_line(s[i]);
        if (pars(&cmd, split(s[i], ' ')))
        {
            ft_free_list(&cmd);
            ft_free(s);
            glob.exit_code = 258;
            return (NULL);
        }
    }
    free(line);
    ft_free(s);
    return (cmd);
}
