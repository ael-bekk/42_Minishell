#include "../inc/minishell.h"

char *find_var(char *to_find, char **env)
{
    int i;
    char *tmp;

    i = -1;
    while (env && env[++i])
    {
        if (!ft_strncmp(to_find, env[i], strlen(to_find)) && env[i][strlen(to_find)] == '=')
        {
            tmp = ft_substr(env[i], strlen(to_find) + 1, strlen(env[i]));
            free(to_find);
            return (tmp);
        }
    }
    free(to_find);
    return (ft_strdup(""));
}

char    *expand(char *l, char **env, int exit_code, char *av)
{
    char *line;
    int i;
    int left;

    left = 0;
    i = -1;
    line = NULL;
	if (!l)
		return(NULL);
    while (l[++i])
    {
        if (l[i] == '\'')
            while (l[++i] && l[i] != '\'')
                ;
        if (l[i] == '$' && ft_isdigit(l[i + 1]))
        {
            line = ft_strjoin_freed2(line, ft_substr(l, left, i - left), 1);
            if (l[i + 1] == '0')
                line = ft_strjoin_freed(line, &av[2], 1);
            else
                line = ft_strjoin_freed(line, "", 1);
            left = ++i + 1;
        }
        else if (l[i] == '$' && l[i + 1] == '?')
        {
            line = ft_strjoin_freed2(line, ft_substr(l, left, i - left), 1);
            line = ft_strjoin_freed2(line, ft_itoa(exit_code), 1);
            left = ++i + 1;
        }
        else if (l[i] == '$' && (l[i + 1] == '\'' || l[i + 1] == '\"' || l[i + 1] == '_' || ft_isalpha(l[i + 1])))
        {
            line = ft_strjoin_freed2(line, ft_substr(l, left, i - left), 1);
            left = ++i;
            while (l[i] && (ft_isalnum(l[i]) || l[i] == '_'))
                i++;
            line = ft_strjoin_freed2(line, find_var(ft_substr(l, left, i - left), env), 1);
            left = i;
            i--;
        }
    }
    line = ft_strjoin_freed2(line, ft_substr(l, left, i - left), 1);
    free(l);
    return (line);
}
