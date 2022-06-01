/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_hand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amounadi < ael-bekk and amounadi >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 05:06:22 by amounadi          #+#    #+#             */
/*   Updated: 2022/05/30 05:06:26 by amounadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	last_new_line(void)
{
	int	i;
	int	last;
	int	new;

	i = -1;
	last = 0;
	new = 0;
	while (rl_line_buffer[++i])
	{
		if (rl_line_buffer[i] == '\n')
		{
			last = new;
			new = i + 1;
		}
	}
	return (last);
}

static void	ft_plus_sig(void)
{
	if (last_new_line() && !g_glob.no_init)
		printf("\r\033[0m%s  ", &rl_line_buffer[last_new_line() + 1]);
	else if (!g_glob.no_init)
		printf("\r\033[0;34m~> %s%% \033[0m%s  ", CYAN, rl_line_buffer);
	if (!g_glob.no_init)
		printf("\n");
	rl_replace_line("", 0);
	print_prompet();
	rl_on_new_line();
	rl_redisplay();
}

void	sig_hnd(int sig)
{
	(void)sig;
	if (!g_glob.pid && g_glob.p == -2)
	{
		printf("\n");
		g_glob.exit_code = 130;
	}
	if (g_glob.p != -1 && g_glob.p != -2)
	{
		g_glob.exit_code = 130;
		g_glob.no_init = 1;
		printf("\r");
		printf("%s%s  \n", g_glob.herd, rl_line_buffer);
		rl_redisplay();
		close(0);
	}
	else if (g_glob.p == -1)
		ft_plus_sig();
}

void	sig_hnd2(int sig)
{
	(void)sig;
	printf("\r     %s  \r", rl_line_buffer);
	rl_on_new_line();
	rl_redisplay();
}
