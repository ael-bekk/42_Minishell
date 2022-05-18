#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

//****************************************************************************//
//                     Including relative header files                        //
//****************************************************************************//

#include "../libft/libft.h"
#include "./built_in.h"

//****************************************************************************//
//                           Add some colors colors                           //
//****************************************************************************//

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

//****************************************************************************//
//                                    Title                                   //
//****************************************************************************//

# define TITLE "------------------------------------------------------------------------------------------\n\
            ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n\
            ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n\
            ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n\
            ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n\
            ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n\
            ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n\
                                                                   \n"

//****************************************************************************//
//                               Some defines                                 //
//****************************************************************************//

# define TRUE 1
# define FALSE 0
# define DQUOTE "\033[0;32mdquote> \033[0;37m"
# define QUOTE "\033[0;32mquote> \033[0;37m"

//****************************************************************************//
//                                  Stracters                                 //
//****************************************************************************//

typedef struct s_cmd
{
    int             in;
    int             out;
    char            **here_doc;
    char            **rid; // < > >> whith type 1 2 3 
    int             *type; // (1 : <) , (2 : >) , (3 : >>) 
    char            **cmd; // cmd , flags, args
    struct s_cmd    *next;
}   t_cmd;

typedef struct s_glob
{
    int     no_nl;
    int     not_set_new_prompet;
    int     p;
    int     exit_code;
    char    **av;
    char    **exec_env;
    t_list  *local;
    t_list  *env;
    
}   t_glob;

//****************************************************************************//
//                               One golob var                                //
//****************************************************************************//

t_glob  glob;

//****************************************************************************//
//                             signal_hanling                                 //
//****************************************************************************//

void    sig_hnd(int sig);
void    sig_hnd2(int sig);

//****************************************************************************//
//                                   prompt                                   //
//****************************************************************************//
char    *deppace_name(char *s)
void    prompet_user(t_list *tmp)
void    prompet_computername(t_list *tmp)
int     cherch_file();
void    prompet();
void    print_prompet();



void    split_f(char **s, char no_splt);
char    **split(char *l, char no_splt);

t_cmd   *parsing(char *line);

t_cmd   *creat_node(void);
t_cmd   *ft_nodelast(t_cmd *head);
void    add_back_node(t_cmd **head, t_cmd *new);

char    *separ_line(char *s);

int     pars_error(char **s);

void    ft_free(char **s);
void    ft_free_list(t_cmd **head);

int     aloccate_data(t_cmd *new, char **s);
void    insertData(t_cmd *new, char **s);

char    *expand(char *l, char *av);
char    *handel_quote(char *line);
char    *delete_quote(char *str);

char	*find_var(char *key, t_list *env);

char	*handler_pipe(char *line);
char	*check_full(char *line);
int		check_quote(char *str);
int		print_quote(char *str);
char    *handl_unclosed(char *inp);
int check_pipe(char *str);





int     equal_place(char *s);
void    copy_data_env(char **ev);

#endif
