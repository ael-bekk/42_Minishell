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

int execution(t_cmd *cmd)
{
    if (!cmd)
        return (0);
    if (!ft_strncmp(cmd->cmd[0], "cd", 3))
    {
        if (cmd->cmd[1])
            return (blt_cd(cmd->cmd[1]));
        else
            return (blt_cd("/"));
    }
    if (!ft_strncmp(cmd->cmd[0], "echo", 5))
        return (blt_echo(&cmd->cmd[1]));
    if (!ft_strncmp(cmd->cmd[0], "pwd", 4))
        return (blt_pwd());

    if (!ft_strncmp(cmd->cmd[0], "env", 4))
        return (blt_env(*cmd->env));
    if (!ft_strncmp(cmd->cmd[0], "exit", 5))
        return (blt_exit(&cmd->cmd[1]));
    return (0);
}

int main(int ac, char **av, char **env)
{
    int exit_code;
    t_cmd *cmd;
    char *inp;

    exit_code = 0;
    printf("%s", TITLE);
    while (TRUE)
    {
        printf("%s", BLUE);
        blt_pwd();
        signal(SIGINT, sig_hnd);
        signal(SIGQUIT, sig_hnd2);
        inp = readline("\033[0;34m-> % \033[0;37m");
        if (!inp)
        {
            printf("exit\n");
            exit(0);
        }
        add_history(inp);
        inp = handel_quote(inp);
        inp = expand(inp, env, exit_code, av[0]);
        cmd = parsing(inp, &exit_code, env);
        exit_code = execution(cmd);
        //affiche(cmd);
    }
    return (0);
}
