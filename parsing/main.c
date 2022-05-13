#include "../inc/minishell.h"

void    affiche(t_cmd *cmd)
{ 
    while (cmd)
    {
        int i = -1;
        printf("\n---------------------------\n");
        printf("here_doc : \n");
        while(cmd->here_doc[++i])
            printf("[%s] --- ", cmd->here_doc[i]);
        printf("\n");
        i = -1;
        printf("rid : \n");
        while(cmd->rid[++i])
            printf("[%s -- %d] --- ", cmd->rid[i], cmd->type[i]);
        printf("\n");
        i = -1;
        printf("cmd : \n");
        while(cmd->cmd[++i])
            printf("[%s] ", cmd->cmd[i]);
        printf("\n");
        cmd = cmd->next;
    }
}

int main(int ac, char **av, char **env)
{
    int exit_code;
    t_cmd *cmd;
    char *inp;
    char *s;

    exit_code = 0;
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
        inp = handel_quote(inp);
        inp = expand(inp, env, exit_code);
        cmd = parsing(inp, &exit_code);
        //exit_code = execution(cmd);
        affiche(cmd);
    }
    return (0);
}
