#include "../inc/minishell.h"

int last_new_line()
{
    int i;
    int last;
    int new;

    i = -1;
    last = 0;
    new = 0;
    while (rl_line_buffer[++i])
        if (rl_line_buffer[i] == '\n')
        {
            last = new;
            new = i + 1;
        }
    return (last);
}

void sig_hnd(int sig)
{

    (void)sig;
    if (glob.p != -1)
    {
        close(0);
        printf("\n");
    }
    else if (glob.p == -1)
    {
        if (last_new_line())
            printf("\r\033[0m%s  ", &rl_line_buffer[last_new_line() + 1]);
        else
            printf("\r\033[0;34m~> %s%% \033[0m%s  ", CYAN, rl_line_buffer);
        rl_replace_line("", 0);
        printf("\n");
        print_prompet();
        rl_on_new_line();
        rl_redisplay();
    }
}

void    sig_hnd2(int sig)
{
    (void)sig;

    printf("\r     %s  \r", rl_line_buffer);
    rl_on_new_line();
    rl_redisplay();
}
