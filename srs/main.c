#include "../inc/minishell.h"



int main()
{
    char *inp;
    char *s;

    printf("%s", TITLE);
    while (TRUE)
    {
        s = getcwd(NULL, 0);
        printf("%s%s\n", BLUE, s);
        signal(SIGINT, sig_hnd);
        inp = readline("\033[0;34m-> % \033[0;37m");
        if (inp == NULL)
        {
            printf("exit\n");
            exit(0);
        }
        add_history(inp);
        parsing(inp);
    }
    return (0);
}