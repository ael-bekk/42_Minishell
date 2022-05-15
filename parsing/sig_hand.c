#include "../inc/minishell.h"

void sig_hnd(int sig)
{
    char *s;

    (void)sig;
    if (!glob.p)
    {
        printf("\n");
        exit(1);
    }
    else if (glob.p == -1)
    {
        printf("\r\033[0;34m-> %% \033[0;37m%s  ", rl_line_buffer);
        rl_replace_line("", 0);
        s = getcwd(NULL, 0);
        printf("\n%s%s\n", BLUE, s);
        rl_on_new_line();
        rl_redisplay();
        free(s);
    }
}

void    sig_hnd2(int sig)
{
    (void)sig;

    printf("\r     %s  \r", rl_line_buffer);
    rl_on_new_line();
    rl_redisplay();
}
