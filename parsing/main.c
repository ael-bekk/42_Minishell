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
    if (!cmd || !cmd->cmd[0])
        return (0);
    // if (!ft_strncmp(cmd->cmd[0], "cd", 3))
    //     return (blt_cd(cmd->cmd[1]));
    if (!ft_strncmp(cmd->cmd[0], "echo", 5))
        return (blt_echo(&cmd->cmd[1]));
    if (!ft_strncmp(cmd->cmd[0], "pwd", 4))
        return (blt_pwd());
    if (!ft_strncmp(cmd->cmd[0], "env", 4))
        return (blt_env());
    if (!ft_strncmp(cmd->cmd[0], "exit", 5))
        return (blt_exit(&cmd->cmd[1]));
    if (!ft_strncmp(cmd->cmd[0], "unset", 6))
        return (blt_unset(&cmd->cmd[1]));
    // if (!ft_strncmp(cmd->cmd[0], "export", 7))
    //     return (blt_export(&cmd->cmd[1]));
    return (0);
}

int main(int ac, char **av, char **ev)
{
    t_cmd *cmd;
    char *inp;

    copy_data_env(ev);
    glob.exit_code = 0;
    printf("%s", TITLE);
    while (TRUE)
    {
        glob.p = -1;
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
        inp = handl_unclosed(inp);
        if (inp)
            add_history(inp);
        inp = expand(inp, av[0]);
        cmd = parsing(inp);
        if (cmd)
            glob.exit_code = execution(cmd);
        //affiche(cmd);
        ft_free_list(&cmd); 
    }
    return (0);
}
