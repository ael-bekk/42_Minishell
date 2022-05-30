#include "../inc/minishell.h"
int	check_spece_pipe(char *str)
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
int	check_space_and(char *str)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	if (str[i] == '&')
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

int	check_space(char *str)
{
	while (*str)
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}
