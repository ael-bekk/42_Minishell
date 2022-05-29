#include "../inc/minishell.h"

int	check_line_or_and(char *str)
{
	char	c;

	while (*str && (*str == ' ' || *str == '\n'))
		str++;
	if (*str && (*str == '|' || *str == '&'))
	{
		c = *str;
		str++;
		while (*str && (*str == ' ' || *str == '\n'))
			str++;
		if (!*str || *str == '&' || *str == '|')
		{
			p_error(c);
			glob.error = 1;
			return (0);
		}
	}
	return (1);
}

int	check_line_pipe(char *str)
{
	char	c;

	while (*str && (*str == ' ' || *str == '\n'))
		str++;
	if (*str && (*str == '|' || *str == '&'))
	{
		c = *str;
		str++;
		while (*str && (*str == ' ' || *str == '\n'))
			str++;
		if (!*str)
		{
			p_error(c);
			glob.error = 1;
			return (0);
		}
	}
	return (1);
}

int	check_space_pipe(char *str)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	if (str[i] == '|')
	{
		a = i;
		i++;
		while (str[i] && (str[i] == '\n' || str[i] == ' '))
			i++;
		if (str[i] && str[i] == '|' && a + 1 != i)
		{
			p_error(str[i]);
			glob.error = 1;
			return (0);
		}
	}
	return (1);
}

int	skip_qoute_inside(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '"')
	{
		i++;
		while (str[i] && str[i] != '"')
			i++;
		return (i);
	}
	else
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		return (i);
	}
}
