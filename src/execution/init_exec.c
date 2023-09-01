/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:51:01 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 10:51:02 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struc_pipe(t_pipe *d, char *infile, char *outfile, t_exe *exe)
{
	(void)exe;
	d->infile = infile;
	d->outfile = outfile;
}

void	init_pipes_beginning(t_pipe *pip)
{
	pip->fd_pipe1[0] = -1;
	pip->fd_pipe1[1] = -1;
	pip->fd_pipe2[0] = -1;
	pip->fd_pipe2[1] = -1;
}

void	fill_builtins_tab(t_exe *exe)
{
	exe->last_append = NULL;
	exe->builtins[0] = "cd";
	exe->builtins[1] = "echo";
	exe->builtins[2] = "env";
	exe->builtins[3] = "exit";
	exe->builtins[4] = "export";
	exe->builtins[5] = "pwd";
	exe->builtins[6] = "unset";
	exe->builtins[7] = NULL;
}

void	setup_terminal(int mode, t_exe *exe)
{
	if (mode == 0)
	{
		if (tcgetattr(STDIN_FILENO, &exe->tp) == -1)
			write(2, "error getattr\n", 14);
		ft_memcpy(&exe->save, &exe->tp, sizeof(struct termios));
		exe->tp.c_lflag = exe->tp.c_lflag & (~ECHOCTL);
		if (tcsetattr(STDIN_FILENO, TCSANOW, &exe->tp) == -1)
			write(2, "error setattr\n", 14);
	}
	else if (mode == 1)
	{
		if (tcsetattr(STDIN_FILENO, TCSANOW, &exe->save) == -1)
			write(2, "error setattr\n", 14);
	}
}
