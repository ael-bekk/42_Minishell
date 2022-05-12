#include "../inc/minishell.h"

void    affiche(t_cmd *cmd)
{ 
    while (cmd)
    {
        int i = -1;
        printf("\n---------------------------\n");
        printf("here_doc : \n");
        while(cmd->here_doc[++i])
            printf("%s --- ", cmd->here_doc[i]);
        printf("\n");
        i = -1;
        printf("rid : \n");
        while(cmd->rid[++i])
            printf("[%s -- %d] --- ", cmd->rid[i], cmd->type[i]);
        printf("\n");
        i = -1;
        printf("cmd : \n");
        while(cmd->cmd[++i])
            printf("%s ", cmd->cmd[i]);
        printf("\n");
        cmd = cmd->next;
    }
}

int main()
{
    t_cmd *cmd;
    char *inp;
    char *s;

    printf("%s", TITLE);
    while (TRUE)
    {
        s = getcwd(NULL, 0);
        printf("%s%s\n", BLUE, s);
        signal(SIGINT, sig_hnd);
        inp = readline("\033[0;34m-> % \033[0;37m");
        if (!inp)
        {
            printf("exit\n");
            exit(0);
        }
        add_history(inp);
        cmd = parsing(inp);
        affiche(cmd);
    }
    return (0);
}
