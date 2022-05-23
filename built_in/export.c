#include "../inc/minishell.h"

void	print_export(int fd)
{
		char **str;
        int i;

        i = -1;
        str = list_to_str(glob.local);
        ft_sort_arry(str);
        while(str[++i])
        {
            ft_putstr_fd("declare -x ",fd);
            ft_putstr_fd(str[i],fd);
            ft_putstr_fd("\n",fd);
        }
        ft_free(str);
}

t_list  *find_var2(char *key, t_list *env)
{
    char *tmp;

    while (env)
    {
        if (!ft_strncmp(key, env->key, strlen(env->key) + 1))
            return (env);
        env = env->next;
    }
    return (NULL);
}

int is_valid_var(char *s)
{
    int i;
    int p_m;

    i = 0;
    if (!ft_isalpha(s[0]))
    {
        printf("%s: export: `%s': not a valid identifier\n", glob.av[0], s);
        return (0);
    }
    while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
        i++;
    if (!s[i])
        return (0);
    if (s[i] == '+' && s[i + 1] == '=')
        return (1);
    if (s[i] == '=')
        return (2);
    printf("%s: export: `", glob.av[0]);
    p_m = (s[i] == '=');
    i = 0;
    while (s[i] && ((s[i] != '=' && p_m) || !p_m))
        printf("%c", s[i++]);
    printf("': not a valid identifier\n");
    return (0);
}

int blt_export(char **cmd, t_list **g,int fd)
{
    t_list  *node;
    int     i;
    int     p;
    int     type;
    int     ret;

    i = -1;
    ret = 0;
	if (!cmd[0])
	{
		print_export(fd);
		return(0);
	}
    while (cmd && cmd[++i])
    {
        type = is_valid_var(cmd[i]);
        if (type)
        {
            p = equal_place(cmd[i]);
            cmd[i][p - (type == 1)] = 0;
            node = find_var2(cmd[i], *g);
            if (!node)
            {
                ft_lstadd_back(g, ft_lstnew(ft_strdup(cmd[i]), ft_strdup(&cmd[i][p + 1])));
                type = 0;
            }
        }
        if (type == 1 && node)
            node->value = ft_strjoin_freed(node->value, &cmd[i][p + 1], 1);
        if (type == 2 && node)
        {
            free(node->value);
            node->value = ft_strdup(&cmd[i][p + 1]);
        }
        ret += !type;
    }
    return (ret != 0);
}
