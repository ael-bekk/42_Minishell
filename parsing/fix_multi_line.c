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
