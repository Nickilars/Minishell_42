/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:50:47 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 10:50:48 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_cmd(t_pipe *d, t_exe *exe)
{
	if (d->infile)
	{
		setup_infile_cmd(d, exe);
	}
	if (d->outfile)
	{
		setup_outfile_cmd(d, exe);
	}
	else
	{
		if (dup2 (d->fd_pipe1[1], STDOUT_FILENO) == -1)
			perror_msg_system(4, exe);
		close(d->fd_pipe1[1]);
	}
}

void	last_cmd(t_pipe *d, int process, t_exe *exe)
{
	if (d->infile)
	{
		setup_infile_cmd(d, exe);
	}
	else
	{
		if (process == 0)
		{
			if (dup2 (d->fd_pipe2[0], STDIN_FILENO) == -1)
				perror_msg_system(4, exe);
			close(d->fd_pipe2[0]);
		}
		if (process == 1)
		{
			if (dup2 (d->fd_pipe1[0], STDIN_FILENO) == -1)
				perror_msg_system(4, exe);
			close(d->fd_pipe1[0]);
		}
	}
	if (d->outfile)
	{
		setup_outfile_cmd(d, exe);
	}
}

void	middle_cmd(t_pipe *d, t_exe *exe, int process)
{
	(void)exe;
	if (d->infile)
	{
		setup_infile_cmd(d, exe);
	}
	else
	{
		if (process == 0)
			setup_middle_cmd(d, 0, exe);
		if (process == 1)
			setup_middle_cmd(d, 1, exe);
	}
	if (d->outfile)
		setup_outfile_cmd(d, exe);
	else
	{
		if (process == 0)
			setup_middle_cmd(d, 2, exe);
		if (process == 1)
			setup_middle_cmd(d, 3, exe);
	}
}
