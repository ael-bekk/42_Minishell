#ifndef PARSING_H
#define PARSING_H


typedef struct s_cmd
{
	int             use;
	int             t_type;
	int             in;
	int             out;
	char            **here_doc;
	char            **rid; // < > >> whith type 1 2 3
	int             *type; // (1 : <) , (2 : >) , (3 : >>)
	char            **cmd; // cmd , {flags/args..}
	struct s_cmd    *next;
}   t_cmd;


int     pars_error(char **s);

//****************************************************************************//
//                                   parsing                                  //
//****************************************************************************//

void    clear_line(char *inp);
void    split_f(char **s, char no_splt);
char    **split(char *l, char no_splt);
char    *separ_line(char *s);
int     pars(t_cmd **cmd, char **splt);
t_cmd    *parsing(char *line);

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
void	insertData(t_cmd *nw, char **s);
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
