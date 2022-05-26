#include "../inc/minishell.h"

char    *change_wild2(char *s)
{
    int i;
    int q;
    char *new;

    i = -1;
    new = ft_strdup(s);
    while (new[++i])
    {
        if (new[i] == '\'' || new[i] == '\"')
        {
            q = new[i];
            while (new[++i] && q != new[i])
                    new[i] = new[i] * (new[i] != '*') -4 * (new[i] == '*');
        }
    }
    return (new);
}

char *delete_quote2(char *str)
{
	int i;
	int j;
	char c;
	char *line;
	int a;

	i = 0;
	j = 0;
	c = 0;
	a = 0;
	if (!str)
		return (NULL);
	line = malloc(ft_strlen(str) + 1);
	while (str && str[i])
	{
		if ((c == 0 || c == str[i]) && str[i] == -2)
		{
			c = str[i++];
			if (++a == 2)
			{
				c = 0;
				a = 0;
			}
		}
		else
			line[j++] = str[i++];
	}
	line[j] = '\0';
	free(str);
	return (line);
}

void    insertData(t_cmd *new, char **s)
{
    int h;
    int r;
    int c;
    int i;

    h = 0;
    r = 0;
    c = 0;
    i = -1;
    while (s && s[++i])
    {
        if (s[i][0] == '<' && s[i][1] == '<')
        {
            new->t_type = ft_strchr(s[++i], '\'') || ft_strchr(s[i], '\"');
            clear_line(s[i]);
            new->here_doc[h++] = delete_quote(ft_strdup(s[i]));
        }
        else if ((s[i][0] == '>' || s[i][0] == '<'))
        {
            new->type[r] = (s[i][0] == '<')
                + 2 * (s[i][0] == '>' && !s[i][1])
                + 3 * (s[i][0] == '>' && s[i][1] == '>');
            new->rid[r++] = delete_quote2(delete_quote(expand(ft_strdup(s[++i]))));
            if (!new->rid[r - 1] || !new->rid[r - 1][0])
            {
                free(new->rid[r - 1]);
                new->rid[r - 1] = ft_strdup(" ");
                new->rid[r - 1][0] = -3;
                new->rid[r - 1] = ft_strjoin_freed(new->rid[r - 1], s[i], 1);
            }
            wild(delete_quote(change_wild2(s[i])));
            if (glob.line_c)
            {
                free(new->rid[r - 1]);
                new->rid[r - 1] = NULL;
                new->rid = ft_str_double_join(&(new->rid), glob.line, glob.red, glob.line_c);
                r = ft_double_strlen(new->rid);
                glob.line_c = 0;
            }
        }
        else
        {
            new->cmd[c++] = delete_quote2(delete_quote(expand(ft_strdup(s[i]))));
            if (!ft_strrchr(s[i], '\"') && !ft_strrchr(s[i], '\'') && (!new->cmd[c - 1] || !new->cmd[c - 1][0]))
            {
                free(new->cmd[--c]);
                new->cmd[c] = NULL;
            }
            wild(delete_quote(change_wild2(s[i])));
            if (glob.line_c)
            {
                free(new->cmd[c - 1]);
                new->cmd[c - 1] = NULL;
                new->cmd = ft_str_double_join(&(new->cmd), glob.line, glob.cmd, glob.line_c);
                c = ft_double_strlen(new->cmd);
                glob.line_c = 0;
            }
        }
    }
}