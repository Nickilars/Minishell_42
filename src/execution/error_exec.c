/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:50:30 by nrossel           #+#    #+#             */
/*   Updated: 2023/09/01 11:10:14 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void	command_not_found(char *cmd)
{
	if (cmd && cmd[0] == '/')
	{
		printf("Minishell: %s: No such file or directory\n", cmd);
		g_errno = 1;
	}
	else if (cmd)
	{
		printf("Minishell: %s: command not found\n", cmd);
		g_errno = 127;
	}
	else
	{
		write(2, "Minishell: : command not found\n", 31);
		g_errno = 127;
	}
}

int	perror_msg_system(int errn, t_exe *exe)
{
	(void) exe;
	if (errn == 1)
		perror("Fork");
	else if (errn == 2)
		perror("Pipe");
	else if (errn == 3)
		perror("Execve");
	else if (errn == 4)
		perror("Dup2");
	else if (errn == 5)
		perror("Dup");
	else if (errn == 6)
		perror("Close");
	else if (errn == 7)
		perror("Open");
	else if (errn == 0)
	{
		perror("");
	}
	setup_terminal(1, exe);
	exit (g_errno);
}
