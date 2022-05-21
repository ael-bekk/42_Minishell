#include "../inc/minishell.h"

char *deppace_name(char *s)
{
    char *c;
    int l;
    int r;

    r = 0;
    while (s && s[r] && s[r] != '>')
        r++;
    l = ++r;
    while (s && s[r] && s[r] != '<')
        r++;
    c = ft_substr(s, l, r - l);
    free(s);
    return (c);
}

int cherch_file()
{
    int fd;
    char *env[2];
    char *s;

    fd = open("/Library/Preferences/SystemConfiguration/preferences.plist", O_RDONLY);
    s = get_next_line11(fd);
    while (s)
    {
        if (ft_strnstr(s, "ComputerName", ft_strlen(s)))
        {
            env[0] = ft_strjoin_freed2(ft_strdup("COMPUTER="), deppace_name(get_next_line11(fd)), 1);
            env[1] = NULL;
            blt_export(env, &glob.local);
            free(env[0]);
            free(s);
            close(fd);
            return (1);
        }
        free(s);
        s = get_next_line11(fd);
    }
    free(s);
    close(fd);
    return (0);
}

void    prompet_user(t_list *tmp)
{
    if (tmp)
        ft_lstadd_back(&glob.local,
        ft_lstnew(ft_strdup("USER"), ft_strdup(tmp->value)));
    else
        ft_lstadd_back(&glob.local,
        ft_lstnew(ft_strdup("USER"), ft_strdup("USER")));
}

void    prompet_computername(t_list *tmp)
{
    if (tmp)
        ft_lstadd_back(&glob.local,
            ft_lstnew(ft_strdup("COMPUTER"), ft_strdup(tmp->value)));
    else
        ft_lstadd_back(&glob.local,
            ft_lstnew(ft_strdup("COMPUTER"), ft_strdup("COMPUTER")));
}

void    prompet()
{
    t_list *tmp;

    tmp = find_var2("USER", glob.env);
    if (!cherch_file())
        prompet_computername(tmp);
    prompet_user(tmp);
    ft_lstadd_back(&glob.local,
        ft_lstnew(ft_strdup("PS1"),
        ft_strjoin_freed2(ft_strjoin_freed(ft_strdup(tmp->value), "@", 1),
        ft_strdup(find_var2("COMPUTER", glob.local)->value), 1)));
}