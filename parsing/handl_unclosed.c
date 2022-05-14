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

char *handl_unclosed(char *inp)
{
    int p1[2];
    t_back_up *backup;

    backup = vars();
    pipe(p1);
    backup->p = fork();
    if (!backup->p)
    {
        //signal(SIGINT, sig_h);
        inp = handel_quote(inp);
        close(p1[0]);
        close(p1[1]);
        exit(1);
    }
    wait(NULL);
    backup->p = 0;
    close(p1[0]);
    close(p1[1]);
    return (inp);
}