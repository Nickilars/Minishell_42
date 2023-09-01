/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:50:19 by nrossel           #+#    #+#             */
/*   Updated: 2023/09/01 11:32:18 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_cmd(t_pipe *pip, t_exe *exe, t_shell *d_shell, char *cmd)
{
	int	fork_pid;
	int	status;

	fork_pid = fork();
	if (fork_pid == -1)
	{
		perror_msg_system(1, exe);
	}
	if (fork_pid == 0)
	{
		prepare_cmd(exe, d_shell, cmd);
		handle_dup_fd_single_cmd(pip, exe);
		if (execve(exe->cmd_path, exe->cmd_n_arg, exe->env_cpy) == -1)
		{
			perror_msg_system(3, exe);
		}
		exit(ERROR);
	}
	waitpid(fork_pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_errno = WEXITSTATUS(status);
	}
}

void	handle_dup_fd_single_cmd(t_pipe *pip, t_exe *exe)
{
	handle_redirections(exe, pip);
	if (pip->infile)
	{
		setup_infile_cmd(pip, exe);
	}
	if (pip->outfile)
	{
		setup_outfile_cmd(pip, exe);
	}
}

void	prepare_cmd(t_exe *exe, t_shell *d_shell, char *cmd)
{
	t_list	*path;

	path = find_var_env(d_shell->env, "PATH");
	if (path)
	{
		exe->path = path->valeur;
		exe->access_path = ft_split_exe(exe->path, ':', 1);
	}
	else
	{
		exe->path = NULL;
		exe->access_path = NULL;
	}
	exe->cmd_n_arg = ft_split_exe(cmd, ' ', 0);
	if (access (exe->cmd_n_arg[0], F_OK) == 0)
	{
		exe->cmd_path = exe->cmd_n_arg[0];
	}
	else
		exe->cmd_path = get_cmd_path(exe->cmd_n_arg[0], exe);
}

void	child_0(t_pipe *pip, t_exe *exe, t_shell *d_shell, char *cmd)
{
	int		fork_pid;

	if (pip->fd_pipe1[0] != 0 || pip->fd_pipe1[1] != 0)
		close_pipes(pip, 1);
	setup_pipes(pip, 0, exe);
	fork_pid = fork();
	save_pid(exe, fork_pid);
	if (fork_pid == -1)
		perror_msg_system(1, exe);
	if (fork_pid == 0)
	{
		close_pipes(pip, 2);
		prepare_cmd(exe, d_shell, cmd);
		handle_redirections(exe, pip);
		if (exe->cmd_number == 0)
			first_cmd(pip, exe);
		else if (exe->cmd_number == exe->nb_of_pipes)
			last_cmd(pip, 0, exe);
		else
			middle_cmd(pip, exe, 0);
		if (execve (exe->cmd_path, exe->cmd_n_arg, exe->env_cpy) == -1)
			perror_msg_system(3, exe);
		exit(ERROR);
	}
	close_pipes(pip, 4);
}

void	child_1(t_pipe *d, t_exe *exe, t_shell *d_shell, char *cmd)
{
	int		fork_pid;

	if (d->fd_pipe2[0] != 0 || d->fd_pipe2[1] != 0)
		close_pipes(d, 4);
	setup_pipes(d, 1, exe);
	fork_pid = fork();
	save_pid(exe, fork_pid);
	if (fork_pid == -1)
		perror_msg_system(1, exe);
	if (fork_pid == 0)
	{
		close(d->fd_pipe1[1]);
		close(d->fd_pipe2[0]);
		prepare_cmd(exe, d_shell, cmd);
		handle_redirections(exe, d);
		if (exe->cmd_number == exe->nb_of_pipes)
			last_cmd(d, 1, exe);
		else
			middle_cmd(d, exe, 1);
		if (execve (exe->cmd_path, exe->cmd_n_arg, exe->env_cpy) == -1)
			perror_msg_system(3, exe);
		exit(ERROR);
	}
	close_pipes(d, 1);
}
