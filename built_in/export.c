#include "../inc/minishell.h"

int ft_double_strlen(char **s)
{
    int i;

    i = 0;
    while (s && s[i])
        i++;
    return (i);
}

int is_valid_var(char *s)
{
    int i;

    i = -1;
    if (!s || !ft_isalpha(s[0]))
        return (0);
    while (s[++i] && (ft_isalnum(s[i]) || s[i] == '_'))
        ;
    if (s[i] == '=' && s[i] != '=')
        return (1);
    return (0);
}

int blt_export(char **cmd, char ***env)
{
    int i;
    int lent;
    int j;
    char **tmp;

    lent = ft_double_strlen(cmd);
    tmp = *env;
    *env = copy_data(*env, lent);
    ft_free(tmp);
    i = -1;
    lent = ft_double_strlen(*env);
    while (cmd && cmd[++i])
    {
        if (is_valid_var(cmd[i]))
            (*env)[lent++] = ft_strdup(cmd[i]);
        else
        {
            printf("Minishell: export: `");
            j = 0;
            while (cmd[i][j] && cmd[i][j] != '=')
                printf("%c", cmd[i][j++]);
            printf("': not a valid identifier\n");
        }
    }
    (*env)[lent] = NULL;
    return (0);
}