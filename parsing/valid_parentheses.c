#include "../inc/minishell.h"


char    *skip_qoute(char *str)
{
    if (*str == '"')
    {
        str++;
        while(*str && *str != '"')
            str++;
        return (++str);
    }
    else
    {
        str++;
        while(*str && *str != '\'')
            str++;
        return (++str);
    }

}

int check_error_parentheses(int a, char c, char s)
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
	int i;
	int a;
    int y;
    char *stack;
    
    stack = malloc(ft_strlen(s) + 1);
	a = 0;
	i = 0;
    y = 0;
	while (*s)
	{
        if (*s == '\'' || *s == '"')
            s = skip_qoute(s);
		if (*s == '(')
        {
			stack[a++] = *s++;
            y = i++;
            while(*s && *s++ == ' ' && ++i)
                y++;
        }
        if (a && *s == ')' && stack[a - 1] == '(' && y + 1 != i && s++)
			a--;
		if (*s == ')')
        {
            a = 1;
            break;
        }
        if(*s && *s != '"' && *s != '\'' && *s != '(' && *s != ')' && ++i) 
            s++;
    }
	if (check_error_parentheses(a, *s, stack[a - 1]))   
		return (0);    
    return (1);
}
