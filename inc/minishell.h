/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 05:27:45 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 05:58:36 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

//****************************************************************************//
//                     Including relative header files                        //
//****************************************************************************//

# include "../libft/libft.h"
# include "./built_in.h"

typedef struct s_cmd
{
	int				use;
	int				t_type;
	int				in;
	int				out;
	char			**here_doc;
	char			**rid;
	int				*type;
	char			**cmd;
	struct s_cmd	*next;
}	t_cmd;

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
# define SYNTAX_ERROR "\033[4;31m Minishell: syntax error: unexpected end of file\n\033[0m"
//****************************************************************************//
//                                  Stracters                                 //
//****************************************************************************//

typedef struct s_glob
{
	char	*line[100000000];
	int		line_c;
	int		cmd;
	int		red;
	char	*d_name;
	char	*old_inp;
	int		last_in;
	pid_t	pid;
	pid_t	pid_cmd;
	int		nb_cmd;
	int		no_init;
	char	*herd;
	int		pip;
	int		no_nl;
	int		p;
	int		exit_code;
	char	**av;
	char	**exec_env;
	int		error;
	t_list	*local;
	t_list	*env;
}	t_glob;

//****************************************************************************//
//                               One golob var                                //
//****************************************************************************//

t_glob	g_glob;

//****************************************************************************//
//                             signal_hanling                                 //
//****************************************************************************//

void	sig_hnd(int sig);
void	sig_hnd2(int sig);

//****************************************************************************//
//                                   prompt                                   //
//****************************************************************************//

char	*deppace_name(char *s);
void	prompet_user(t_list *tmp);
void	prompet_computername(t_list *tmp);
int		cherch_file(void);
void	prompet(void);
void	print_prompet(void);

//****************************************************************************//
//                                 befor exec                                 //
//****************************************************************************//

int		in_file(t_cmd *cmd, char *s);
int		here_doc(t_cmd *cmd, char *limiter);
int		appand_file(t_cmd *cmd, char *s);
int		out_file(t_cmd *cmd, char *s);
int		define_cmd(t_cmd *cmd);
int		errors_return(char *s);
int		errors_return_red(char *s, t_cmd *cmd);
char	**list_to_str(t_list *head);
void	ft_sort_arry(char **str);
char	*delete_quote2(char *str);
void	wild(char *ll);
void	p_error(char c);
int		check_line_pipe(char *str);
int		check_line_or_and(char *str);
int		valid_parentheses(char *s);
char	*skip_qoute(char *str);
int		skip_qoute_inside(char *str);
void	delete_parentheses(char *line);
int		search_in_dir(char *d, char **pfix_sfix, char **n_f, int l);
void	search_in_dir2(char *d, char **pfix_sfix, char **n_f, int l);
void	search_in_dir3(char *d, char **pfix_sfix, char **new_p_s, char **new_d);
int		is_matching(char *dir, char *to_search);
int		check_space_and(char *str);
int		check_spece_pipe(char *str);
int		check_space(char *str);
char	*change_wild2(char *s);

//****************************************************************************//
//                                   parsing                                  //
//****************************************************************************//

int		pars_error(char **s);
void	clear_line(char *inp);
void	split_f(char **s, char no_splt);
char	**split(char *l, char no_splt);
char	*separ_line(char *s);
int		pars(t_cmd **cmd, char **splt);
t_cmd	*parsing(char *line);

//****************************************************************************//
//                              execution                                    //
//****************************************************************************//

int		check_built(char *cmd);
int		exec_built(t_cmd *cmd);
int		print_check_error(char *str);
int		check_path(char **str, t_list *path);
void	close_all(t_cmd *cmd);
void	exec_cmd(t_cmd *cmd, t_cmd *cmd2);
int		execution(t_cmd *cmd);

//****************************************************************************//
//                                 t_list data                                //
//****************************************************************************//

t_cmd	*creat_node(void);
t_cmd	*ft_nodelast(t_cmd *head);
void	insertdata(t_cmd *nw, char **s);
void	copy_data_env(char **ev);
void	add_back_node(t_cmd **head, t_cmd *nw);
void	ft_free_list(t_cmd **head);
char	*find_var(char *key, t_list *env);
t_list	*find_var2(char *key, t_list *env);
int		equal_place(char *s);
int		allocatedata(t_cmd *cmd, int h_doc, int rid, int cmnd);
int		aloccate_data(t_cmd *cmd, char **s);

//****************************************************************************//
//                        quote and dquote ( " | ' )                          //
//****************************************************************************//

char	*handel_quote(char *line);
char	*delete_quote(char *str);
char	*handler_pipe(char *line);
char	*check_full(char *line);
int		check_quote(char *str);
int		print_quote(char *str);
char	*handl_unclosed(char *inp);
int		check_pipe(char *str, int len);
char	*expand(char *l);
char	*expand2(char *l);
void	f1(char **line, char *l, int *ll, int *r);
void	f2(char **line, char *l, int *ll, int *r);
void	f3(char **line, char *l, int *ll, int *r);

//****************************************************************************//
//                              || and &&                                    //
//****************************************************************************//

void	or_and(char *line);
char	*handler_or_and(char *line);
int		check_or_and(char *str);
void	mini_cmd(char *line);

#endif
