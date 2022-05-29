#include "../inc/minishell.h"

void	delete_parentheses(char *str)
{
	while (*str)
	{
		if (*str == 34 || *str == 39)
			str = skip_qoute(str);
		if (*str == 40 || *str == 41)
			*str = ' ';
		str++;
	}
}

char	*skip_qoute(char *str)
{
	if (*str == '"')
	{
		str++;
		while (*str && *str != '"')
			str++;
		return (++str);
	}
    else
    {
		str++;
		while (*str && *str != '\'')
			str++;
		return (++str);
	}
}

int	check_error_parentheses(int a, char c, int s)
{
    if (a != 0)
    {
        if (c == ')')
            p_error(c);
        else
            p_error(s);
        glob.error = 1;
		return (0);    
    }
    return (1);
}

int	valid_parentheses(char *s)
{
	int		i;
	int		a;
    int		y;
    char	*stack;
    
    stack = malloc(ft_strlen(s) + 1);
	a = 0;
	i = 0;
    y = 0;
	while (*s)
	{
		if (*s == '\'' || *s == '"')
			s = skip_qoute(s);
		else if (*s == '(')
		{
			stack[a++] = *s++;
		   	y = i++;
			while(*s && ( *s == ' ' || *s == '|' || *s == '&') && i++)
			{
				if (*s == '|' || *s == '&')
				{
					p_error (*s);
					glob.error = 1;
					free (stack);
					return (0);
				}
				y++;
				s++;
			}
		}
		else if (a && *s == ')' && stack[a - 1] == '(' && y + 1 != i && ++i && s++)
			a--;
		else if (*s == ')')
		{
			a = 1;
			break ;
		}
		else if (++i && s++)
            ;
    }
	y = stack[a - 1];
	free(stack);
	if (check_error_parentheses(a, *s,y))
		return (0);
	return (1);
}
