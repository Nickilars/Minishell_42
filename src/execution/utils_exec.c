/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:51:13 by nrossel           #+#    #+#             */
/*   Updated: 2023/09/01 15:02:51 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strjoin_exec(char const *s1, char const *s2, t_exe *exe)
{
	char	*cs1;
	char	*cs2;
	char	*result;
	int		i;
	int		j;

	cs1 = (char *)s1;
	cs2 = (char *)s2;
	i = 0;
	j = 0;
	result = my_malloc(((ft_strlen(cs1)) + (ft_strlen(cs2)) + 1),
			sizeof(char), &exe->trash_x);
	if (result == NULL)
		return (NULL);
	while (cs1[i])
		result[j++] = cs1[i++];
	result[j] = ' ';
	i = 0;
	while (cs2[i])
		result[j++] = cs2[i++];
	result[j] = '\0';
	return (result);
}

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s2)
		return (NULL);
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s2);
}

void	save_pid(t_exe *exe, int pid)
{
	exe->save_pid[exe->idx] = pid;
}

void	single_builtin(t_exe *exe, t_pipe *pip, t_shell *shell_info)
{
	int		out_backup;
	int		in_backup;

	g_errno = 0;
	create_cmd_n_args_builtins(exe, &exe->trash_x);
	in_backup = dup(0);
	out_backup = dup(1);
	if (in_backup == -1 || out_backup == -1)
		perror_msg_system(5, exe);
	handle_dup_fd_single_cmd(pip, exe);
	builtins_x(exe->cmd_n_arg[0], shell_info, exe->cmd_n_arg, exe);
	dup2(in_backup, 0);
	dup2(out_backup, 1);
	if (in_backup == -1 || out_backup == -1)
		perror_msg_system(5, exe);
}
