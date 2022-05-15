#ifndef BUILT_IN_H
#define BUILT_IN_H

int     blt_cd(char *path, char ***env);
int     blt_echo(char **cmd);
int     blt_pwd();
int     blt_env(char **cmd);
int     blt_exit(char **cmd);
int     blt_unset(char **cmd, char **env);
int     blt_export(char **cmd, char ***env);

#endif