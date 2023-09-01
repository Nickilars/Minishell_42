/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:51:05 by nrossel           #+#    #+#             */
/*   Updated: 2023/09/01 15:37:25 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ending_last_or_unique_cmd(t_exe *exe, int *status)
{
	if (WIFEXITED(status))
	{
		if (exe->cmd_not_found == 127)
			g_errno = 127;
		else
		{
			g_errno = WEXITSTATUS(status);
		}
	if (WIFSIGNALED(status))
	{
		g_errno = 128 + WTERMSIG(status);
		setup_terminal(1, exe);
	}
	}
}

static void ending(t_exe* exe)
{
	int	i;
	int	status;

	i = 0;
	if (exe->nb_of_pipes > 0)
	{
		while (i < (exe->nb_of_pipes) + 1)
		{
			waitpid(exe->save_pid[i], &status, 0);
			if (WIFEXITED(status))
			{
				if(exe->cmd_not_found == 127)
					g_errno = 127;
				else
				{
					g_errno = WEXITSTATUS(status);
				}
				if (WIFSIGNALED(status))
				{
					g_errno = 128 + WTERMSIG(status);
					setup_terminal(1, exe);
				}
			}
			i++;
		}
	}
	ending_last_or_unique_cmd(exe, &status);
}

int	shell_execution(t_exe *exe, t_shell *shell_info)
{
	t_pipe	pip;

	init_pipes_beginning(&pip);
	fill_builtins_tab(exe);
	heredoc_start(exe);
	exe->save_pid = my_malloc(sizeof(int), exe->nb_of_pipes + 1, &exe->trash_x);
	signals_update();
	if (exe->save_pid == NULL)
		return (SUCCESS);
	if (exe->nb_of_pipes == 0)
		execution_no_pipe(exe, &pip, shell_info);
	if (exe->nb_of_pipes > 0)
		execution_with_pipes(exe, &pip, shell_info);
	ending(exe);
	exe->cmd_number = 0;
	exe->idx = 0;
	exe->cmd_not_found = 0;
	sig_default();
	return (SUCCESS);
}
