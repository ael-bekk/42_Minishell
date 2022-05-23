#include "../inc/minishell.h"
#include <dirent.h>

int is_matching(char *dir, char *to_search, int it_1, int it_2)
{
    if (!dir[it_1] && !to_search[it_2])
        return (1);
    if (!dir[it_1] && to_search[it_2] == '*')
        return (is_matching(dir, to_search, it_1, it_2 + 1));
    if (!dir[it_1] || !to_search[it_2])
        return (0);
    if (to_search[it_2] != '*' && to_search[it_2] != dir[it_1])
        return (0);
    if (to_search[it_2] != '*' && to_search[it_2] == dir[it_1])
        return (is_matching(dir, to_search, it_1 + 1, it_2 + 1));
    return (is_matching(dir, to_search, it_1 + 1, it_2 + 1)
        || is_matching(dir, to_search, it_1, it_2 + 1)
        || is_matching(dir, to_search, it_1 + 1, it_2));
}

int check_dir(char *path)
{
    DIR *dir = opendir(path);

    free(path);
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
            new_d = ft_strjoin_freed(ft_strdup(new_d), p->d_name, 1);
            new_p_s[0] = ft_strjoin_freed(ft_strdup(pfix_sfix[0]), p->d_name, 1);
            new_p_s[0] = ft_strjoin_freed(ft_strdup(new_p_s[0]), "/", 1);
            new_p_s[1] = pfix_sfix[1];
            if (!n_f[l + 1] && (check_dir(new_d) ||  pfix_sfix[1][0] == ' '))
                printf("%s%s%s", pfix_sfix[0], p->d_name, pfix_sfix[1]);
            else
            {
                
                search_in_dir(new_d, new_p_s, n_f, l + 1);
            }
            
        }
        
        p = readdir(dir);
    }
    return (0);
}

int main(int ac, char **av)
{
    int i;
    char *path;
    char *p_s_fix[2];
    char **s;

    i = -1;
    path = ft_strdup(".");
    p_s_fix[0] = ft_strdup("");
    s = ft_split(av[1], '/');
    if (av[1][0] == '/')
        path[0] = '/';
    
    if (av[1][ft_strlen(av[1]) - 1] == '/')
        p_s_fix[1] = ft_strdup("/ ");
    else
        p_s_fix[1] = ft_strdup(" ");
    
    while (av[1][++i] == '/')
        p_s_fix[0] = ft_strjoin_freed(p_s_fix[0], "/", 1);
    i = 0;
    while (!ft_strchr(s[i], '*'))
    {
        path = ft_strjoin_freed(path, "/", 1);
        path = ft_strjoin_freed(path, s[i], 1);
        p_s_fix[0] = ft_strjoin_freed(p_s_fix[0], s[i], 1);
        p_s_fix[0] = ft_strjoin_freed(p_s_fix[0], "/", 1);
        i++;
    }
    search_in_dir(path, p_s_fix, &s[i], 0);
    
    return (0);
}

// #include "../inc/minishell.h"
// #include <dirent.h>

// int is_matching(char *dir, char *to_search, int it_1, int it_2)
// {
//     if (!dir[it_1] && !to_search[it_2])
//         return (1);
//     if (!dir[it_1] && to_search[it_2] == '*')
//         return (is_matching(dir, to_search, it_1, it_2 + 1));
//     if (!dir[it_1] || !to_search[it_2])
//         return (0);
//     if (to_search[it_2] != '*' && to_search[it_2] != dir[it_1])
//         return (0);
//     if (to_search[it_2] != '*' && to_search[it_2] == dir[it_1])
//         return (is_matching(dir, to_search, it_1 + 1, it_2 + 1));
//     return (is_matching(dir, to_search, it_1 + 1, it_2 + 1)
//         || is_matching(dir, to_search, it_1, it_2 + 1)
//         || is_matching(dir, to_search, it_1 + 1, it_2));
// }

// typedef struct s_wildcard
// {
//     char    *path;
//     char    *prefix;
//     char    *suffix;
//     char    **n_f;
//     int         l;
// }   t_wildcard;

// // int check_dir(char *path)
// // {
// //     DIR *dir = opendir(path);

// //     free(pa)
// //     if (!dir)
// //         return (0);
// //     closedir(dir);
// //     return (1);
// // }

// int search_in_dir(t_wildcard wild)
// {
//     DIR         *dir;
//     struct      dirent *p;
//     t_wildcard  new_wild;

//     dir = opendir(wild.path);
//     if (!dir)
//         return (0);
//     new_wild = wild;
//     p = readdir(dir);
//     while (p)
//     {
//         if (is_matching(p->d_name, wild.n_f[wild.l], 0, 0) && p->d_name[0] != '.')
//         {
//             if (!wild.n_f[wild.l + 1])
//                 printf("%s%s%s", wild.prefix, p->d_name, wild.suffix);
//             else
//             {
//                 new_wild.path = ft_strjoin_freed(ft_strdup(wild.path), "/", 1);
//                 new_wild.path = ft_strjoin_freed(ft_strdup(new_wild.path), p->d_name, 1);

//                 new_wild.prefix = ft_strjoin_freed(ft_strdup(wild.prefix), p->d_name, 1);
//                 new_wild.prefix = ft_strjoin_freed(ft_strdup(new_wild.prefix), "/", 1);
//                 new_wild.l++;
//                 search_in_dir(new_wild);
//             }
//         }
//         p = readdir(dir);
//     }
//     closedir(dir);
//     printf("\n");
//     return (0);
// }

// int main(int ac, char **av)
// {
//     t_wildcard p;

//     int i;
//     char **s;
    
//     i = -1;
//     p.path = ft_strdup(".");
//     p.prefix = ft_strdup("");
    
//     s = ft_split(av[1], '/');
//     if (av[1][0] == '/')
//         p.path[0] = '/';
    
//     if (av[1][ft_strlen(av[1]) - 1] == '/')
//         p.suffix = ft_strdup("/ ");
//     else
//         p.suffix = ft_strdup(" ");
    
//     while (av[1][++i] == '/')
//         p.prefix = ft_strjoin_freed(p.prefix, "/", 1);
//     i = 0;
//     while (!ft_strchr(s[i], '*'))
//     {
//         p.path = ft_strjoin_freed(p.path, "/", 1);
//         p.path = ft_strjoin_freed(p.path, s[i], 1);
//         p.prefix = ft_strjoin_freed(p.prefix, s[i], 1);
//         p.prefix = ft_strjoin_freed(p.prefix, "/", 1);
//         i++;
//     }
//     p.n_f = &s[i];
//     p.l = 0;
//     search_in_dir(p);
    
//     return (0);
// }