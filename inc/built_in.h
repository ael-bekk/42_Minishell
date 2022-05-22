#ifndef BUILT_IN_H
#define BUILT_IN_H

int     blt_cd(char *path);
int     blt_echo(char **cmd, int fd_out);
int     blt_pwd(char *s, int fd_out);
int     blt_env(char *s, int fd_out);
int     blt_exit(char **cmd);
int     blt_unset(char **cmd);
int     blt_export(char **cmd, t_list **g);

#endif