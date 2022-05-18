#include "../inc/minishell.h"

/*void print_all(char **cmd)
{
    int i;

    i = -1;
    while (cmd && cmd[++i])
    {
        printf("%s", cmd[i]);
        if (cmd[i + 1])
            printf(" ");
    }
}

int nl_echo(char *s)
{
    int i;

    i = 0;
    while (s && s[0] == '-' && s[++i])
        if (s[i] != 'n')
            return (0);
    if (s && !s[i])
        return (1);
    return (0);
}

int blt_echo(char **cmd)
{
    int i;

    i = 0;
    while (cmd && cmd[i] && nl_echo(cmd[i]))
        i++;
    print_all(&cmd[i]);
    if (!nl_echo(cmd[0]) && (cmd[i] || !i))
        printf("\n");
    else if (cmd[i] && cmd[i][ft_strlen(cmd[i]) - 1] != '\n' && nl_echo(cmd[0]))
        glob.no_nl = 1;
    return (0);
}*/

// echo - 
// echo -  hjkh

int check_and_print(char *str, char **cmd, int a)
{
	int i;

	i = 0;
	if (!a)
	{
		if (str && (str[0] != '-' || !str[1]))
			return(0);
		while(str && str[++i])
			if (str[i] != 'n')
				return (0);
	}
	else
	{
		while(cmd  && cmd[i])
		{
			printf("%s",cmd[i++]);
			if(cmd[i])
				printf(" ");
		}
		if (a == 1)
			printf("\n");
	}
	return(1);
}

int blt_echo(char **cmd)
{
	int	i;
	int	nl;

	i = 1;
	nl = 0;
	nl = check_and_print(cmd[0], cmd, 0);
	if(nl && cmd[0])
	{
		while(cmd && cmd[i] && nl)
			nl = check_and_print(cmd[i++], cmd, 0);
		if (!nl)
			i--;
		check_and_print(cmd[0], &cmd[i], 2);
	}
	else
		check_and_print(cmd[0], cmd, 1);
	return(0);
}
