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
            new->here_doc[h++] = delete_quote(ft_strdup(s[i]));
        }
        else if ((s[i][0] == '>' || s[i][0] == '<'))
        {
            new->type[r] = (s[i][0] == '<')
                + 2 * (s[i][0] == '>' && !s[i][1])
                + 3 * (s[i][0] == '>' && s[i][1] == '>');
            new->rid[r++] = delete_quote(expand(ft_strdup(s[++i])));
            if (!new->rid[r - 1] || !new->rid[r - 1][0])
            {
                printf("\033[4;31m  %s: %s: ambiguous redirect\033[0m\n", &glob.av[0][2], s[i]);
                new->use = 0;
            }
            else
                new->rid[r - 1] = delete_quote(new->rid[r - 1]);
        }
        else
            new->cmd[c++] = delete_quote2(delete_quote(expand(ft_strdup(s[i]))));
    }
}