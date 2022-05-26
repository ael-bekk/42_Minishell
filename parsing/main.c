#include "../inc/minishell.h"

void    mini_cmd(char *line)
{
    t_cmd *cmd;

    cmd = parsing(line);
    if (cmd && !define_cmd(cmd))
        glob.exit_code = execution(cmd);
    ft_free_list(&cmd);
}

int main(int ac, char **av, char **ev)
{
    char *inp;

    glob.av = av;
    copy_data_env(ev);
    printf("%s", TITLE);
    prompet();
    while (TRUE)
    {
        glob.error = 0;
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
        if (inp && inp[0])
            inp = handl_unclosed(inp);
        if (inp && inp[0] && ft_strcmp(glob.old_inp, inp))
        {
            free(glob.old_inp);
            glob.old_inp = ft_strdup(inp);
            add_history(inp);
        }
        or_and(inp);
        free(inp);
    }
    return (0);
}
