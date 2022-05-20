#include "../inc/minishell.h"

int    open_pipes(t_cmd *cmd)
{
    int p[2];

    cmd->in = STDIN_FILENO;
    while (cmd->next)
    {
        if (pipe(p) == ERROR_SYS_CALL)
            return (errors_return("pipe"));
        cmd->out = p[1];
        cmd = cmd->next;
        cmd->in = p[0];
    }
    cmd->out = STDOUT_FILENO;
    return (0);
}

int read_from_here_doc(t_cmd *cmd)
{
    int i;

    while (cmd && glob.p == -1)
    {
        i = -1;
        while (cmd->here_doc[++i] && glob.p == -1)
            here_doc(cmd, cmd->here_doc[i]);
        cmd = cmd->next;
    }
    glob.p = -1;
    return (glob.exit_code);
}

int open_files(t_cmd *cmd, int (*t[4])(t_cmd *, char *))
{
    int i;

    while (cmd && glob.p == -1)
    {
        i = -1;
        while (cmd->rid[++i] && glob.p == -1)
            t[cmd->type[i]](cmd, cmd->rid[i]);
        cmd = cmd->next;
    }
    return (0);
}

int    define_cmd(t_cmd *cmd)
{
    int    (*t[4])(t_cmd *, char *);

    glob.p = -1;
    t[1] = in_file;
    t[2] = out_file;
    t[3] = appand_file;
    glob.exit_code = 0;
    if (open_pipes(cmd))
        return (0);
    if (read_from_here_doc(cmd))
        return (0);
    if (open_files(cmd, t))
        return (0);
    return (glob.exit_code);
}