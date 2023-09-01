/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:50:44 by nrossel           #+#    #+#             */
/*   Updated: 2023/09/01 14:07:33 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_name_cmd_builtins(t_exe *exe, char *name);

void	builtins_0(t_pipe *pip, t_exe *exe, t_shell *d_shell)
{
	int		fork_pid;

	if (pip->fd_pipe1[0] != 0 || pip->fd_pipe1[1] != 0)
		close_pipes(pip, 1);
	setup_pipes(pip, 0, exe);
	fork_pid = fork();
	if (fork_pid == -1)
		perror_msg_system(1, exe);
	if (fork_pid == 0)
	{
		close_pipes(pip, 2);
		create_cmd_n_args_builtins(exe, &exe->trash_x);
		if (exe->cmd_not_found == 127)
			exit(127);
		handle_redirections(exe, pip);
		if (exe->cmd_number == 0)
			first_cmd(pip, exe);
		else if (exe->cmd_number == exe->nb_of_pipes)
			last_cmd(pip, 0, exe);
		else
			middle_cmd(pip, exe, 0);
		builtins_x(exe->cmd_n_arg[0], d_shell, exe->cmd_n_arg, exe);
		exit(SUCCESS);
	}
	close_pipes(pip, 4);
}

void	builtins_1(t_pipe *d, t_exe *exe, t_shell *d_shell)
{
	int		fork_pid;

	if (d->fd_pipe2[0] != 0 || d->fd_pipe2[1] != 0)
		close_pipes(d, 4);
	setup_pipes(d, 1, exe);
	fork_pid = fork();
	if (fork_pid == -1)
		perror_msg_system(1, exe);
	if (fork_pid == 0)
	{
		close_pipes(d, 3);
		create_cmd_n_args_builtins(exe, &exe->trash_x);
		if (exe->cmd_not_found == 127)
			exit(127);
		handle_redirections(exe, d);
		if (exe->cmd_number == exe->nb_of_pipes)
			last_cmd(d, 1, exe);
		else
			middle_cmd(d, exe, 1);
		builtins_x(exe->cmd_n_arg[0], d_shell, exe->cmd_n_arg, exe);
		exit(SUCCESS);
	}
	close_pipes(d, 1);
}

void	create_cmd_n_args_builtins(t_exe *exe, t_dlist **trash)
{
	char	*arg;
	char	**name;
	size_t	size;

	size = ft_strlen(exe->tab_cmd[exe->idx]);
	name = ft_split((exe->tab_cmd[exe->idx]), ' ', trash);
	exe->cmd_n_arg = my_malloc(3, sizeof(char **), trash);
	exe->cmd_n_arg[0] = my_malloc(ft_strlen(name[0] + 1),
			sizeof(char *), trash);
	fill_name_cmd_builtins(exe, name[0]);
	if (ft_strlen(name[0]) < size && g_errno != 127)
	{
		arg = my_malloc((ft_strlen(exe->tab_cmd[exe->idx])
					+ (ft_strlen(name[0] + 1))) + 1, sizeof(char*), trash);
		exe->cmd_n_arg[1] = my_malloc((ft_strlen(arg))
				+ 1, sizeof(char *), trash);
		arg = ft_strcpy(arg, exe->tab_cmd[exe->idx] + (ft_strlen(name[0]) + 1));
		exe->cmd_n_arg[1] = arg;
	}
}

static void	fill_name_cmd_builtins(t_exe *exe, char *name)
{
	if (ft_strncmp("echo", name, 5) == 0)
		exe->cmd_n_arg[0] = "echo";
	else if (ft_strncmp("cd", name, 3) == 0)
		exe->cmd_n_arg[0] = "cd";
	else if (ft_strncmp("env", name, 4) == 0)
		exe->cmd_n_arg[0] = "env";
	else if (ft_strncmp("exit", name, 5) == 0)
		exe->cmd_n_arg[0] = "exit";
	else if (ft_strncmp("export", name, 7) == 0)
		exe->cmd_n_arg[0] = "export";
	else if (ft_strncmp("pwd", name, 4) == 0)
		exe->cmd_n_arg[0] = "pwd";
	else if (ft_strncmp("unset", name, 6) == 0)
		exe->cmd_n_arg[0] = "unset";
	else
	{
		command_not_found(exe->tab_cmd[exe->idx]);
		exe->cmd_not_found = 127;
		g_errno = 127;
	}
}
