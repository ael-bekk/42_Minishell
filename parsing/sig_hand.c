/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_hand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:45:58 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/05/29 04:47:30 by amounadi         ###   ########.fr       */
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
	if (last_new_line() && !glob.no_init)
		printf("\r\033[0m%s  ", &rl_line_buffer[last_new_line() + 1]);
	else if (!glob.no_init)
		printf("\r\033[0;34m~> %s%% \033[0m%s  ", CYAN, rl_line_buffer);
	if (!glob.no_init)
		printf("\n");
	rl_replace_line("", 0);
	print_prompet();
	rl_on_new_line();
	rl_redisplay();
}

void	sig_hnd(int sig)
{
	(void)sig;
	if (!glob.pid && glob.p == -2)
	{
		printf("\n");
		glob.exit_code = 130;
	}
	if (glob.p != -1 && glob.p != -2)
	{
		glob.exit_code = 130;
		glob.no_init = 1;
		printf("\r");
		printf("%s%s  \n", glob.herd, rl_line_buffer);
		rl_redisplay();
		close(0);
	}
	else if (glob.p == -1)
		ft_plus_sig();
}

void	sig_hnd2(int sig)
{
	(void)sig;
	printf("\r     %s  \r", rl_line_buffer);
	rl_on_new_line();
	rl_redisplay();
}
