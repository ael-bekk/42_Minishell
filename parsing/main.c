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

int main(int ac, char **av, char **ev)
{
    t_cmd *cmd;
    char *inp;

    glob.exec_env = ev;
    glob.av = av;
    copy_data_env(ev);
    prompet();
    printf("%s", TITLE);
    while (TRUE)
    {
        glob.nb_cmd = 0;
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
            glob.exit_code = execution(cmd);
        //affiche(cmd);
        ft_free_list(&cmd); 
    }
    return (0);
}
