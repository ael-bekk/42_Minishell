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
    if (!ft_strncmp(cmd->cmd[0], "cd", 3))
        return (blt_cd(cmd->cmd[1]));
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
    if (!ft_strncmp(cmd->cmd[0], "export", 7))
        return (blt_export(&cmd->cmd[1], &glob.env));
    return (glob.exit_code);
}

void    clear_line(char *inp)
{
    int i;
    int j;

    i = -1;
    j = 0;
    if (!inp)
        return ;
    while (inp[++i])
        if (inp[i] != '$' || (inp[i + 1] != '\"' && inp[i + 1] != '\''))
            inp[j++] = inp[i];
    inp[j] = '\0';
}

int main(int ac, char **av, char **ev)
{
    t_cmd *cmd;
    char *inp;

    glob.av = av;
    copy_data_env(ev);
    prompet();
    printf("%s", TITLE);
    while (TRUE)
    {
        glob.p = -1;
        print_prompet();
        signal(SIGINT, sig_hnd);
        signal(SIGQUIT, sig_hnd2);
        inp = readline("\033[0;34m~> \033[0;36m% \033[0m");
        if (!inp)
        {
            printf("exit\n");
            exit(0);
        }
        glob.no_init = 0;
        inp = handl_unclosed(inp);
        if (inp && inp[0])
            add_history(inp);
        clear_line(inp);
        cmd = parsing(inp);
        if (cmd && !define_cmd(cmd))
        {
            glob.exit_code = execution(cmd);
        }
        //affiche(cmd);
        ft_free_list(&cmd); 
    }
    return (0);
}
