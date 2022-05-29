#include "../inc/minishell.h"

char	*handl_unclosed(char *inp)
{
	int i;

	glob.p = -1;
	if ((!check_pipe(inp) || check_quote(inp) || !check_or_and(inp) || check_or_and(inp) == -1) && !glob.error)
	{
		glob.p = dup(0);
		inp = check_full(inp);
		dup(glob.p);
		close(glob.p);
	}
	glob.p = -1;
	if(glob.error)
	{
		free(inp);
		return (NULL);
	}
	return (inp);
}