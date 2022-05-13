#include "../inc/minishell.h"

void sig_hnd(int sig)
{
    char *s;
    (void)sig;
    
    printf("\r\033[0;34m-> %% \033[0;37m%s  ", rl_line_buffer);
    rl_replace_line("", 0);
    s = getcwd(NULL, 0);
    printf("\n%s%s\n", BLUE, s);
    rl_on_new_line();
    rl_redisplay();
}