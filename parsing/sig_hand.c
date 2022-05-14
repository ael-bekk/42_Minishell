#include "../inc/minishell.h"

void sig_hnd(int sig)
{
    char *s;
    t_back_up *backup;

    backup = vars();
    (void)sig;
    if (backup->p)
    {
        printf("\n");
        kill(backup->p, SIGKILL);
        backup->p = 0;
    }
    else
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
