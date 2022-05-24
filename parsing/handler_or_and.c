#include "../inc/minishell.h"

int check_or_and(char *str)
{
	int i;
	int a;

	i = -1;
	a = 0;
	if (!str)
		return(1);
	while (str[++i])
	{
		if (a == 1 && str[i + 1] && ((str[i] == '|' &&  str[i + 1] == '|') || (str[i] == '&' &&  str[i + 1] == '&')))
		{
			a = -1;
			if (str[i] == '&')
				a = 0;
			if (str[i + 1] && ((str[i + 1] == '|' && a == -1) || (str[i + 1] == '&' && a == 0)))
				i++;
		}
		else  if (str[i] != ' ' && str[i] != '\n')
			a = 1;
	}
	return(a);
}

char *handler_or_and(char *line)
{
	char *str;
	int 	a;

	if (!line || !line[0])
		return (NULL);	
	a = check_or_and(line);
	free(glob.herd);
    glob.herd = NULL;
    if (a == 0)
        glob.herd = ft_strdup("cmdand> \033[0;37m");
	else if (a == -1)
        glob.herd = ft_strdup("cmdor> \033[0;37m");
	while (a == -1 || a == 0)
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
		line = ft_strjoin_freed2(line, str, 1);
		a = check_or_and(line);
        	if (a == 0 || a == -1)
        		free(glob.herd);
       		if (a == 0)
			    glob.herd = ft_strdup("cmdand> \033[0;37m");
		    else if(a == -1)
			    glob.herd = ft_strdup("cmdor> \033[0;37m");
	}
	return (line);
}


void	or_and(char *line)
{
	int i;
	int a;
	int check;
	int lent;

	a = 0;
	i = 0;
	check = 1;
	lent = ft_strlen(line);
	while(i < lent)
	{
		a = i;
		while(line[i])
		{
			if(line[i + 1] && ((line[i] == '&' && line[i + 1] == '&') || (line[i] == '|' && line[i + 1] == '|')))
        	{
				line[i] = '\0';
				if ((!glob.exit_code && check == 1) || ((glob.exit_code || a == 0) && check == 2) || !a)
					mini_cmd((line + a));
				check = (line[i + 1] == '&') + 2 * (line[i+1] == '|');
				a = ++i + 1;
			}
			i++;
        }
    }
	if ((!glob.exit_code && check == 1) || ((glob.exit_code || a == 0) && check == 2))
		mini_cmd((line + a));
}

