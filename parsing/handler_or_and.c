#include "../inc/minishell.h"

char *or_and(char *line)
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
				if ((!glob.exit_code && check == 1) || ((glob.exit_code || a == 0) && check == 2))
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