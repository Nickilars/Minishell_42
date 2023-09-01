/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:52:09 by nrossel           #+#    #+#             */
/*   Updated: 2023/09/01 14:10:09 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void	set_signals(void)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_handler = handler_sg;
	sigaction(SIGINT, &sa, NULL);
}

void	sig_default(void)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
}

void	handler_sg(int num)
{
	if (num == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_errno = 130;
	}
}

void	handler_sg_update(int num)
{
	if (num == SIGINT)
	{
		write(1, "\n", 1);
		rl_redisplay();
		g_errno = 130;
	}
	else if (num == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		rl_redisplay();
		g_errno = 131;
	}
}

void	signals_update(void)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler_sg_update;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
}
