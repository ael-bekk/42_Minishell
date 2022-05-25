#include "../inc/minishell.h"
#include <dirent.h>

int is_matching(char *dir, char *to_search, int it_1, int it_2)
{
    if (!dir[it_1] && !to_search[it_2])
        return (1);
    if (to_search[it_2] == dir[it_1])
        return (is_matching(dir, to_search, it_1 + 1, it_2 + 1));
    if (to_search[it_2] == '*')
        return (is_matching(dir, to_search, it_1, it_2 + 1)
            || is_matching(dir, to_search, it_1 + 1, it_2));
    return (0);
}

int check_dir(char *path)
{
    DIR *dir = opendir(path);

    if (!dir)
        return (0);
    closedir(dir);
    return (1);
}

int search_in_dir(char *d, char **pfix_sfix, char **n_f, int l)
{
    DIR *dir = opendir(d);
    if (!dir)
        return (0);
    struct dirent *p;
    char *new_d;
    char *new_p_s[2];

    p = readdir(dir);
    while (p)
    {
        if (is_matching(p->d_name, n_f[l], 0, 0) && p->d_name[0] != '.')
        {
            new_d = ft_strjoin_freed(ft_strdup(d), "/", 1);
            new_d = ft_strjoin_freed(new_d, p->d_name, 1);
            new_p_s[0] = ft_strjoin_freed(ft_strdup(pfix_sfix[0]), p->d_name, 1);
            new_p_s[0] = ft_strjoin_freed(new_p_s[0], "/", 1);
            new_p_s[1] = pfix_sfix[1];
            if (!n_f[l + 1] && (check_dir(new_d) || !pfix_sfix[1][0]))
            {
                glob.line[glob.line_c] = ft_strdup(pfix_sfix[0]);
                glob.line[glob.line_c] = ft_strjoin11(glob.line[glob.line_c], ft_strdup(p->d_name));
                glob.line[glob.line_c] = ft_strjoin11(glob.line[glob.line_c], ft_strdup(pfix_sfix[1]));
                glob.line_c++;
            }
            else
                search_in_dir(new_d, new_p_s, n_f, l + 1);
            free(new_d);
            free(new_p_s[0]);
        }
        p = readdir(dir);
    }
    closedir(dir);
    return (0);
}

void    wild(char *ll)
{
    int i;
    char *path;
    char *p_s_fix[2];
    char c[2];
    char **s;

    glob.line[glob.line_c] = NULL;
    if (!ft_strchr(ll, '*'))
    {
        free(ll);
        return ;
    }
    i = -1;
    c[1] = 0;
    path = ft_strdup(".");
    p_s_fix[0] = ft_strdup("");
    s = ft_split(ll, '/');
    if (ll[0] == '/')
        path[0] = '/';
    
    if (ll[ft_strlen(ll) - 1] == '/')
        p_s_fix[1] = ft_strdup("/");
    else
        p_s_fix[1] = ft_strdup("");
    
    while (ll[++i] == '/' || ll[i] == '.')
    {
        c[0] = ll[i];
        p_s_fix[0] = ft_strjoin11(p_s_fix[0], ft_strdup(c));
    }
    i = 0;
    while (!ft_strchr(s[i], '*'))
    {
        path = ft_strjoin_freed(path, "/", 1);
        path = ft_strjoin_freed(path, s[i], 1);
        i++;
    }
    search_in_dir(path, p_s_fix, &s[i], 0);
    glob.line[glob.line_c] = NULL;
    ft_sort_arry(glob.line);
    free(ll);
    free(path);
    ft_free(s);
    free(p_s_fix[0]);
    free(p_s_fix[1]);
}