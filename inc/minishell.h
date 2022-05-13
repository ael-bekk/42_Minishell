#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define TITLE "------------------------------------------------------------------------------------------\n\
            ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n\
            ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n\
            ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n\
            ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n\
            ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n\
            ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n\
                                                                   \n"

# define TRUE 1
# define FALSE 0

typedef struct s_cmd
{
    char            **here_doc;
    char            **rid; // < > >> whith type 1 2 3 
    int             *type; // (1 : <) , (2 : >) , (3 : >>) 
    char            **cmd; // cmd , flags, args
    char            ***env;
    struct s_cmd    *next;
}   t_cmd;


void    sig_hnd(int sig);
void    sig_hnd2(int sig);
void    split_f(char **s, char no_splt);
char    **split(char *l, char no_splt);
t_cmd   *parsing(char *line, int *exit_code, char **env);
t_cmd   *creat_node(void);
t_cmd   *ft_nodelast(t_cmd *head);
void    add_back_node(t_cmd **head, t_cmd *new);
char    *separ_line(char *s);
int     pars_error(char **s);
void    ft_free(char **s);
void    ft_free_list(t_cmd **head);
int     aloccate_data(t_cmd *new, char **s);
void    insertData(t_cmd *new, char **s);
char    *expand(char *l, char **env, int exit_code, char *av);
char    *handel_quote(char *line);
char    *delete_quote(char *str);
char    **copy_data(char    **s, int plus);
int     ft_double_strlen(char **s);
char *find_var(char *to_find, char **env);

//
int     blt_cd(char *path, char **env);
int     blt_echo(char **cmd);
int     blt_pwd();
int     blt_env(char **cmd);
int     blt_exit(char **cmd);
int     blt_unset(char **cmd, char **env);
int     blt_export(char **cmd, char ***env);

///functions for get_next_line/////
char	*get_next_line(int fd);
char	*ft_strjoin_freed(char *s1, char *s2, int type);
char	*ft_strchr_line(const char *s, int c);
char	*ft_strdup_line(const char *s1);

#endif