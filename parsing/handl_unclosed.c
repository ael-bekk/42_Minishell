#include "../inc/minishell.h"

// void sig_h(int sig)
// {
//     if (sig == SIGINT)
//     {
//         printf("\n");
//         close(0);
//         close(1);
//     }
// }

char *print_data(int fd)
{
    char buff[1024];
    char *line;
    int c;

    line = NULL;
    c = read(fd, buff, 1023);
    while (c > 0)
    {
        buff[c] = '\0';
        line = ft_strjoin_freed(line, buff, 1);
        c = read(fd, buff, 1023);
    }
    return (line);
}

char *handl_unclosed(char *inp)
{
    int i;
    int p1[2];

    if (!check_pipe(inp) ||  check_quote(inp))
    {
        pipe(p1);
        glob.p = fork();
        if (!glob.p)
        {
            //signal(SIGINT, sig_h);
            inp = check_full(inp);
            write(p1[1], inp, ft_strlen(inp));
            close(p1[0]);
            close(p1[1]);
            exit(1);
        }
        wait(NULL);
        close(p1[1]);
        inp = print_data(p1[0]);
        close(p1[0]);
    }
    return (inp);
}