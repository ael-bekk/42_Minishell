#include "../inc/minishell.h"

int is_valid_var2(char *s, char **env)
{
    int i;

    i = 0;
    if (!ft_isalpha(s[0]))
        return (0);
    while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
        i++;
    if (!s[i])
        return (1);
    return (0);
}

int blt_unset(char **cmd, char **env)
{
    int i;
    int j;
    int res;

    res = 0;
    i = -1;
    while (cmd && cmd[++i])
    {
        j = -1;
        res += !is_valid_var2(cmd[i], env);
        while (env && env[++j] && is_valid_var2(cmd[i], env))
        {
            if (!ft_strncmp(cmd[i], env[j], strlen(cmd[i])) && env[j][strlen(cmd[i])] == '=')
            {
                free(env[j]);
                env[j] = NULL;
                while (env[++j])
                    env[j - 1] = env[j];
                env[--j] = NULL;
            }
        }
        if (!is_valid_var2(cmd[i], env))
            printf("Minishell: export: `%s': not a valid identifier\n", cmd[i]);
    }
    return (res != 0);
}