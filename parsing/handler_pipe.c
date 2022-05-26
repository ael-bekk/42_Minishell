#include "../inc/minishell.h"

int		check_spece_pipe(char *str)
{
	int i;
	int a;

	i = 0;
	a = 0;
	if(str[i] == '|')
	{
		a = i;
		i++;
		while(str[i] && (str[i] == '\n' || str[i] == ' '))
			i++;
		if (str[i] && str[i] == '|' && a  + 1 != i )
		{
			p_error(str[i]);
			glob.error = 1;
			return (0);
		}
	}
	return (1);
}


int check_pipe(char *str)
{
	int	i;
	int	a;

	i = -1;
	a = 1;
	if (!str)
		return(1);
	if (str[0] && (str[0] == '|' || str[0] == '&'))
	{
		p_error(str[0]);
		glob.error = 1;
	}
	while (str[++i])
	{
		if (str[i] == '|')
		{
			a = 0;
			if (!check_spece_pipe(str + i))
				return (0);
			if ((str[i + 1] && str[i + 1] == '|') || ( str[i - 1] && str[i - 1] == '|'))
				a = 1;
		}
		else  if (str[i] != ' ' && str[i] != '\n')
			a = 1;
	}
	return(a);
}

char *handler_pipe(char *line)
{
	char *str;
	int 	a;

	if (!line)
		return (NULL);	
	a = !check_pipe(line);
	free(glob.herd);
	glob.herd = NULL;
	glob.herd = ft_strdup("\033[0;32mpipe> \033[0;37m");
	while (a && !glob.error)
	{
		str = readline(glob.herd);
		if (!str)
		{
			if (!glob.no_init)
				ft_putstr_fd("\033[4;31m Minishell: syntax error: unexpected end of file\n\033[0m", 2);
			glob.no_init = 1;
			free(line);
			free(str);
			return (NULL);
		}
		if (!check_line_pipe(str))
		return (NULL);
		line = ft_strjoin_freed2(line, str, 1);
		a = !check_pipe(line);
	}
	return (line);
}
 

char *check_full(char *line)
{
	int v;
	int a;
	
	if (!line)
		return (NULL);
	v = !check_pipe(line) ||  check_quote(line);
	if (!v)
		a = check_or_and(line);
	while (v || a == -1 || a == 0)
	{
		line = handel_quote(line);
		line = handler_pipe(line);
		line = handler_or_and(line);
		v = !check_pipe(line) || check_quote(line);
		if (!v)
			a = check_or_and(line);
		if (glob.error)
		{
			free(line);
			return (NULL);
		}
	}
	return (line);
}
