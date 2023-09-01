/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:50:54 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 10:50:55 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void	close_pipes(t_pipe *d, int process)
{
	if (process == 1)
	{
		close(d->fd_pipe1[0]);
		close(d->fd_pipe1[1]);
	}
	if (process == 2)
	{
		close(d->fd_pipe1[0]);
		close(d->fd_pipe2[1]);
	}
	if (process == 3)
	{
		close(d->fd_pipe1[1]);
		close(d->fd_pipe2[0]);
	}
	if (process == 4)
	{
		close(d->fd_pipe2[1]);
		close(d->fd_pipe2[0]);
	}
}

void	setup_pipes(t_pipe *pip, int process, t_exe *exe)
{
	if (process == 0)
	{
		pip->fd_pipe1[0] = -1;
		pip->fd_pipe1[1] = -1;
		if (exe->cmd_number != exe->nb_of_pipes)
		{
			if (pipe(pip->fd_pipe1) == -1)
				perror_msg_system(2, exe);
		}
	}
	else if (process == 1)
	{
		pip->fd_pipe2[0] = -1;
		pip->fd_pipe2[1] = -1;
		if (exe->cmd_number != exe->nb_of_pipes)
		{
			if (pipe(pip->fd_pipe2) == -1)
				perror_msg_system(2, exe);
		}
	}
}

char	*get_cmd_path(char *cmd, t_exe *exe)
{
	int		i;
	char	*cmd_path;

	i = 0;
	if (cmd)
	{
		if (exe->access_path)
		{
			while (exe->access_path[i])
			{
				cmd_path = strjoin_exec(exe->access_path[i], cmd, exe);
				if (access (cmd_path, F_OK) == 0)
				{
					return (cmd_path);
				}
				else
				i++;
			}
		}
	}
	command_not_found(cmd);
	exit(127);
	return (NULL);
}
