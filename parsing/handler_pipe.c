#include "../inc/minishell.h"

static void	ft_plus(char c, char b, int *q, int a)
{
	if (a == 1 && c && (c == '|' || c == '&'))
	{
		p_error(c);
		glob.error = 1;
	}
	if (a == 2)
	{
		if (!glob.no_init)
			ft_putstr_fd("\033[4;31m Minishell: syntax error:\
				unexpected end of file\n\033[0m", 2);
		glob.no_init = 1;
	}
	if (a == 3)
	{
		if ((c && c == '|') || (b && b == '|'))
			*q = 1;
	}
}

int	check_pipe(char *str)
{
	int	i;
	int	a;
	int	len;

	i = -1;
	a = 1;
	if (!str)
		return (1);
	//ft_plus(str[0], 's', &i, 1);
	len = ft_strlen(str);
	while (++i < len)
	{
		if (str[i] == '\'' || str[i] == '"')
			i += skip_qoute_inside(str + i);
		else if (str[i] == '|' && a--)
		{
			a = 0;
			if (!check_space_pipe(str + i))
				return (0);
			ft_plus(str[i + 1], str[i - 1], &a, 3);
		}
		else if (str[i] != ' ' && str[i] != '\n')
			a = 1;
	}
	return (a);
}

char	*handler_pipe(char *line)
{
	char	*str;
	int		a;

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
			//ft_plus('c', 'c', &a, 2);
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

char	*check_full(char *line)
{
	int	v;
	int	a;

	if (!line)
		return (NULL);
	v = !check_pipe(line) || check_quote(line);
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
