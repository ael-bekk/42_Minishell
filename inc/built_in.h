#ifndef BUILT_IN_H
#define BUILT_IN_H

#include "./parsing.h"

int     blt_cd(char *path);
int     blt_echo(t_cmd *cmd);
int     blt_pwd(t_cmd *cmd);
int     blt_env(t_cmd *cmd);
int     blt_exit(char **cmd);
int     blt_unset(char **cmd);
int     blt_export(char **cmd, t_list **g);

#endif