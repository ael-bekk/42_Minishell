#include "../inc/minishell.h"

int    in_file(t_cmd *cmd, char *s)
{
    if (cmd->in)
        close(cmd->in);
    cmd->in = open(s, O_RDONLY);
    if (cmd->in == ERROR_SYS_CALL)
    {
        cmd->use = 0;
        return (errors_return(s));
    }
    return (0);
}

int match_strings(char *s1, char *s2, int lent, char fin)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (!fin && !s1[i] && !s2[i] && i == lent)
		return (TRUE);
	if (fin && s1[i] == '\n' && i == lent)
		return (TRUE);
	return (FALSE);
}

int    here_doc(t_cmd *cmd, char *limiter)
{
    int i;
    int p[2];
    char *line;
    int cont;

    glob.p = dup(0);
    pipe(p);
    if (cmd->in)
        close(cmd->in);
    cmd->in = p[0];
    line = NULL;
    cont = FALSE;
    free(glob.herd);
    glob.herd = ft_strdup("");
    i = -1;
    while (++i < glob.nb_cmd - 1)
        glob.herd = ft_strjoin11(glob.herd, ft_strdup("pipe "));
    glob.herd = ft_strjoin11(glob.herd, ft_strdup("heredoc> \033[0m"));
    while (cont == FALSE)
    {
        line = readline(glob.herd);
        if (line)
            cont = match_strings(line, limiter, ft_strlen(limiter), 0);
        else
        {
            glob.no_init = 1;
            free(line);
            break;
        }
        if (!cmd->t_type)
            line = expand(line);
        if (cont == FALSE)
        {
            write(p[1], line, ft_strlen(line));
            write(p[1], "\n", 1);
        }
        free(line);
    }
    close(p[1]);
    dup(glob.p);
    close(glob.p);
    glob.p = -1 * !glob.no_init;
    return (glob.exit_code);
}
