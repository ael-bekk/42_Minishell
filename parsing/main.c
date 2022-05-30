/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 05:14:06 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 21:01:30 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	mini_cmd(char *line)
{
	t_cmd	*cmd;

	cmd = parsing(line);
	if (cmd && !define_cmd(cmd))
		g_glob.exit_code = execution(cmd);
	ft_free_list(&cmd);
}

void	minishell(char *inp)
{
	if (!inp)
	{
		printf("exit\n");
		exit(0);
	}
	g_glob.no_init = 0;
	if (inp && inp[0])
		inp = handl_unclosed(inp);
	if (inp && inp[0] && ft_strcmp(g_glob.old_inp, inp))
	{
		free(g_glob.old_inp);
		g_glob.old_inp = ft_strdup(inp);
		add_history(inp);
	}
	or_and(inp);
}

char	*ft_main(char *inp)
{
	g_glob.no_init = 0;
	if (inp && inp[0])
	{
		valid_parentheses(inp);
		inp = handl_unclosed(inp);
	}
	if (inp && inp[0] && ft_strcmp(g_glob.old_inp, inp))
	{
		free(g_glob.old_inp);
		g_glob.old_inp = ft_strdup(inp);
		add_history(inp);
	}
	return (inp);
}

int	main(int ac, char **av, char **ev)
{
	char	*inp;

	(void)ac;
	g_glob.av = av;
	copy_data_env(ev);
	printf("%s", TITLE);
	prompet();
	while (TRUE)
	{
		g_glob.error = 0;
		g_glob.nb_cmd = 0;
		g_glob.p = -1;
		print_prompet();
		signal(SIGINT, sig_hnd);
		signal(SIGQUIT, sig_hnd2);
		inp = readline("\033[0;34m~> \033[0;36m% \033[0m");
		if (!inp)
		{
			printf("exit\n");
			exit(0);
		}
		inp = ft_main(inp);
		or_and(inp);
	}
	return (0);
}
