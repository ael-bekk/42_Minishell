#include "../inc/minishell.h"

int    allocateData(t_cmd *cmd, int h_doc, int rid, int cmnd)
{
    cmd->here_doc = (char **)malloc(sizeof(char *) * (h_doc + 1));
    cmd->rid = (char **)malloc(sizeof(char *) * (rid + 1));
    cmd->type = (int *)malloc(sizeof(int) * (rid + 1));
    cmd->cmd = (char **)malloc(sizeof(char *) * (cmnd + 1));
    if (!cmd->here_doc || !cmd->rid || !cmd->cmd || !cmd->type)
        return (0);
    cmd->here_doc[h_doc] = NULL;
    cmd->rid[rid] = NULL;
    cmd->cmd[cmnd] = NULL;
    return (1);
}

int aloccate_data(t_cmd *cmd, char **s)
{
    int h_doc;
    int rid;
    int cmnd;
    int i;

    h_doc = 0;
    rid = 0;
    cmnd = 0;
    i = -1;
    while (s && s[++i])
    {
        rid += (s[i][0] == '>' && s[i][1] == '>') || (s[i][0] == '<' && !s[i][1]) || s[i][0] == '>';
        h_doc += s[i][0] == '<' && s[i][1] == '<';
        if (s[i][0] == '>' || s[i][0] == '<')
            i++;
        else
            cmnd++;
    }
    if (!cmnd)
        cmd->use = 0;
    return (allocateData(cmd, h_doc, rid, cmnd));
}