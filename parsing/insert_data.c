#include "../inc/minishell.h"

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
            wild(delete_quote(ft_strdup(s[i])));
            if (line)
            {
                free(new->rid[r - 1]);
                new->rid[r - 1] = line;
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
            wild(delete_quote(ft_strdup(s[i])));
            if (line)
            {
                free(new->rid[r - 1]);
                new->rid[r - 1] = line;
            }
        }
    }
}