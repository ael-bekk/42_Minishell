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
#include "./parsing.h"

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
# define ERROR_SYS_CALL -1

//****************************************************************************//
//                                  Stracters                                 //
//****************************************************************************//

typedef struct s_glob
{
    pid_t   pid;
    pid_t   pid_cmd;
    int     nb_cmd;
    int     no_init;
    char    *herd;
    int     pip;
    int     no_nl;
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

char    *deppace_name(char *s);
void    prompet_user(t_list *tmp);
void    prompet_computername(t_list *tmp);
int     cherch_file();
void    prompet();
void    print_prompet();

//****************************************************************************//
//                                 befor exec                                 //
//****************************************************************************//

int    in_file(t_cmd *cmd, char *s);
int    here_doc(t_cmd *cmd, char *limiter);
int    appand_file(t_cmd *cmd, char *s);
int    out_file(t_cmd *cmd, char *s);
int    define_cmd(t_cmd *cmd);
int    errors_return(char *s);


int execution(t_cmd *cmd);

char	**list_to_str(t_list *head);
void    ft_sort_arry(char **str);
char *delete_quote2(char *str);

#endif
