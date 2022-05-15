#include "../inc/minishell.h"

#include <fcntl.h>

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
    char *s;
    char *env[2];

    fd = open("/Library/Preferences/SystemConfiguration/preferences.plist", O_RDONLY);
    if (fd == -1)
        return (0);

    s = get_next_line11(fd);
    while (s)
    {
        if (ft_strnstr(s, "ComputerName", ft_strlen(s)))
        {
            env[0] = ft_strjoin_freed2(ft_strdup("COMPUTER="), deppace_name(get_next_line11(fd)), 1);
            glob.COMPUTER = env[0];
            env[1] = NULL;
            blt_export(env);
            printf("%s", s);
            free(s);
            break ;
        }
        free(s);
        s = get_next_line11(fd);
    }
    return (0);
}

#include <time.h>

int blt_cd(char *path)
{
    int all;

    if (!glob.COMPUTER)
        cherch_file();
    all = 0;
    if (!path || (path[0] == '~' && !path[1]))
    {
        path = find_var("HOME");
        all = 1;
    }
    else if (!ft_strncmp(path, ".", 2))
    {
        printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory");
        return (1);
    }
    else if (chdir(path) == -1)
    {
        printf("Minishell: cd: %s: %s\n", path, strerror(errno));
        if (all)
            free(path);
        return (1);
    }
    if (all)
            free(path);
    return (0);
}