#include "../inc/minishell.h"

int ft_double_strlen(char **s)
{
    int i;

    i = 0;
    while (s && s[i])
        i++;
    return (i);
}

int concatinate_var(char **s, char **env, int len)
{
    char *to_concat;

    (*s)[len] = '\0';
    to_concat = find_var(*s, env);
    (*s)[len++] = '=';
    (*s)[len] = '\0';
    to_concat = ft_strjoin_freed2(ft_strdup(*s), to_concat, 1);
    to_concat = ft_strjoin_freed2(to_concat, ft_strdup(&(*s)[len + 1]), 1);
    free(*s);
    *s = to_concat;
    return (1);
}

int unset_var(char **s, char **env, int len)
{
    char *tmp;
    char *to_concat;
    char c;

    c = (*s)[len];
    (*s)[len] = '\0';
    to_concat = find_var(*s, env);
    tmp = s[1];
    s[1] = NULL;
    blt_unset(s, env);
    s[1] = to_concat;
    return (1);
}

int is_valid_var(char **s, char **env)
{
    int i;
    int p_m;

    i = 0;
    if (!(*s) || !ft_isalpha((*s)[0]))
        return (0);
    while ((*s)[i] && (ft_isalnum((*s)[i]) || (*s)[i] == '_'))
        i++;
    if (!(*s)[i])
        return (0);
    if ((*s)[i] == '+' && (*s)[i + 1] == '=')
        return (concatinate_var(s, env, i));
    if ((*s)[i] == '=')
        return (unset_var(s, env, i));
    printf("Minishell: export: `");
    p_m = ((*s)[i] == '=');
    i = 0;
    while ((*s)[i] && (((*s)[i] != '=' && p_m) || !p_m))
        printf("%c", (*s)[i++]);
    printf("': not a valid identifier\n");
    return (0);
}

int blt_export(char **cmd, char ***env)
{
    int i;
    int lent;
    int type;
    char **tmp;
    int ret;

    tmp = *env;
    *env = copy_data(*env, ft_double_strlen(cmd));
    ft_free(tmp);
    i = -1;
    ret = 0;
    lent = ft_double_strlen(*env);
    while (cmd && cmd[++i])
    {
        type = is_valid_var(&cmd[i], *env);
        ret += type;
        if (type == 1)
            (*env)[lent++] = ft_strdup(cmd[i]);
    }
    (*env)[lent] = NULL;
    return (ret != 0);
}