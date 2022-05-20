#include "../inc/minishell.h"

int    appand_file(t_cmd *cmd, char *s)
{
    if (cmd->out != 1)
        close(cmd->out);
    cmd->out = open(s, O_TRUNC | O_WRONLY | O_CREAT, 0666);
    if (cmd->out == ERROR_SYS_CALL)
        return (errors_return(s));
    return (0);
}

int    out_file(t_cmd *cmd, char *s)
{
    if (cmd->out != 1)
        close(cmd->out);
    cmd->out = open(s, O_APPEND | O_WRONLY | O_CREAT, 0666);
    if (cmd->out == ERROR_SYS_CALL)
        return (errors_return(s));
    return (0);
}