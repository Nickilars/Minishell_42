/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:50:23 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 10:50:24 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_infile_cmd(t_pipe *pip, t_exe *exe)
{
	pip->fd_in = open(pip->infile, O_RDONLY);
	if (pip->fd_in == -1)
	{
		write(2, "error opening infile\n", 21);
		return ;
	}
	if (dup2(pip->fd_in, STDIN_FILENO) == -1)
	{
		perror_msg_system(4, exe);
		return ;
	}
	close(pip->fd_in);
	if (pip->fd_in == -1)
		perror_msg_system(2, exe);
}

void	setup_outfile_cmd(t_pipe *pip, t_exe *exe)
{
	(void)exe;
	if (exe->last_append)
	{
		pip->fd_out = open (pip->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	else
	{
		pip->fd_out = open (pip->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	if (pip->fd_out == -1)
	{
		write(2, "error fd out\n", 13);
		return ;
	}
	if (dup2 (pip->fd_out, STDOUT_FILENO) == -1)
	{
		perror_msg_system(4, exe);
		return ;
	}
	close(pip->fd_out);
	if (pip->fd_out == -1)
		perror_msg_system(2, exe);
}

void	setup_middle_cmd(t_pipe *pip, int option, t_exe *exe)
{
	if (option == 0)
	{
		if (dup2(pip->fd_pipe2[0], STDIN_FILENO) == -1)
			perror_msg_system(4, exe);
		close(pip->fd_pipe2[0]);
	}
	if (option == 1)
	{
		if (dup2(pip->fd_pipe1[0], STDIN_FILENO) == -1)
			perror_msg_system(4, exe);
		close(pip->fd_pipe1[0]);
	}
	if (option == 2)
	{
		if (dup2(pip->fd_pipe1[1], STDOUT_FILENO) == -1)
			perror_msg_system(4, exe);
		close(pip->fd_pipe1[1]);
	}
	if (option == 3)
	{
		if (dup2(pip->fd_pipe2[1], STDOUT_FILENO) == -1)
			perror_msg_system(4, exe);
		close(pip->fd_pipe2[1]);
	}
}
