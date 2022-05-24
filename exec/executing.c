#include "../inc/minishell.h"

int check_built(char *cmd)
{
    int		i;
	char	*str[8];

	str[0] = "echo";
	str[1] = "env";
	str[2] = "cd";
	str[3] = "pwd";
	str[4] = "unset";
	str[5] = "exit";
	str[6] = "export";
    str[7] = NULL;
	i = -1;
    while(cmd && str[++i])
        if (!ft_strncmp(cmd,str[i], ft_strlen(str[0]) + 1))
            return(1);
    return(0);
}

int exec_built(t_cmd *cmd)
{
    if (!cmd || !cmd->cmd[0])
        return (0);
    if (!ft_strncmp(cmd->cmd[0], "cd", 3))
        return (blt_cd(cmd->cmd[1]));
    if (!ft_strncmp(cmd->cmd[0], "echo", 5))
        return (blt_echo(&cmd->cmd[1], cmd->out));
    if (!ft_strncmp(cmd->cmd[0], "pwd", 4))
        return (blt_pwd(cmd->cmd[1], cmd->out));
    if (!ft_strncmp(cmd->cmd[0], "env", 4))
        return (blt_env(cmd->cmd[1], cmd->out));
    if (!ft_strncmp(cmd->cmd[0], "exit", 5))
        return (blt_exit(&cmd->cmd[1]));
    if (!ft_strncmp(cmd->cmd[0], "unset", 6))
        return (blt_unset(&cmd->cmd[1]));
    if (!ft_strncmp(cmd->cmd[0], "export", 7))
        return (blt_export(&cmd->cmd[1], &glob.env, cmd->out, 3)
           || blt_export(&cmd->cmd[1], &glob.local, cmd->out, 2));
    return (glob.exit_code);
}

int check_path(char **str, t_list *path)
{
    int i = -1;
    char **s_path;
    char *p;

    if (!path)
    {
        ft_putstr_fd("Error: PATH doesn't exist\n", 2);
        glob.exit_code = 127;
        return (0);
    }
    s_path = ft_split(path->value, ':');
    while(s_path[++i])
    {
        p = ft_strjoin_freed(ft_strdup(s_path[i]), "/", 1);
        p = ft_strjoin_freed(p, *str, 1);
        if (access(p, X_OK) != -1)
        {
            free(*str);
            *str = p;
            return (1);
        }
        free(p);
    }
    ft_putstr_fd("Error: ", 2);
    ft_putstr_fd(*str, 2);
    ft_putstr_fd(": command not found\n", 2);
    glob.exit_code = 127;
    return (0);
}

void    close_all(t_cmd *cmd)
{
    while (cmd)
    {
        if (cmd->in)
            close(cmd->in);
        if (cmd->out != 1)
            close(cmd->out);
        cmd = cmd->next;
    }
}

void    exec_cmd(t_cmd *cmd, t_cmd *cmd2)
{
    glob.pid_cmd = fork();
    
    if (glob.pid_cmd == 0)
    {
        glob.pid = 1;
        dup2(cmd->in, 0);
        dup2(cmd->out, 1);
        close_all(cmd2);
        if (ft_strchr(cmd->cmd[0], '/') || check_path(&cmd->cmd[0], find_var2("PATH", glob.env)))
        {
            if(execve(cmd->cmd[0], cmd->cmd, glob.exec_env) == -1)
                exit(errors_return(cmd->cmd[0]));
        }
        else
            exit (127);
    }
}

int execution(t_cmd *cmd)
{
    int up_to;
    int old_exit_code;
    t_cmd *cmd2 = cmd;

    glob.p = -2;
    ft_free(glob.exec_env);
    glob.exec_env = list_to_str(glob.env);
    up_to = 1;
    if (glob.nb_cmd == 1 && cmd->use && check_built(cmd->cmd[0]))
        glob.exit_code = exec_built(cmd);
    else
    {
        while(cmd)
        {
            if (cmd->use)
                exec_cmd(cmd, cmd2);
            if (!cmd->next && !cmd->use)
                up_to = 0;
            cmd = cmd->next;
        }
    }
    close_all(cmd2);
    if (up_to)
    {
        waitpid(glob.pid_cmd, &up_to, 0);
        if (!glob.exit_code)
        {
            glob.exit_code = up_to;
            up_to = 1;
        }
        else
            up_to = 0;
    }
    while (wait(NULL) != -1)
        ;
    glob.p = -1;
    return ((glob.exit_code / 256) * up_to + glob.exit_code * !up_to);
}