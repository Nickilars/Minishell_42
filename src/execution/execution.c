/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:50:34 by nrossel           #+#    #+#             */
/*   Updated: 2023/09/01 14:08:27 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution_with_pipes(t_exe *exe, t_pipe *pip, t_shell *shell_info)
{
	int	i;

	i = 0;
	while (i <= exe->nb_of_pipes)
	{
		if (exe->append[exe->idx])
		{
			handle_append(exe);
		}
		if (exe->cmd_number <= exe->nb_of_pipes + 1)
		{
			launch(pip, shell_info, exe, i);
		}
		i++;
		exe->idx++;
		exe->cmd_number++;
	}
}

void	execution_no_pipe(t_exe *exe, t_pipe *pip, t_shell *shell_info)
{
	if (exe->append && exe->append[0])
		handle_append(exe);
	if (exe->tab_cmd[0])
	{
		if (is_builtins(exe->tab_cmd[0], exe->builtins) == 1)
		{
			single_builtin(exe, pip, shell_info);
		}
		else
			single_cmd(pip, exe, shell_info, exe->tab_cmd[0]);
	}
}

void	builtins_x(char *builtin, t_shell *info, char **cmd, t_exe *exe)
{
	int	i;

	i = 0;
	info->arg = cmd;
	if (ft_strncmp("echo", builtin, ft_strlen(builtin)) == 0)
		echo_minishell(*(exe->cmd_n_arg + 1), &info->trash_lst);
	else if (ft_strncmp("cd", builtin, ft_strlen(builtin)) == 0)
		cd_minishell(info, *(exe->cmd_n_arg + 1));
	else if (ft_strncmp("env", builtin, ft_strlen(builtin)) == 0)
		env_minishell(info, *(exe->cmd_n_arg + 1));
	else if (ft_strncmp("exit", builtin, ft_strlen(builtin)) == 0)
		exit_minishell(*(exe->cmd_n_arg + 1), &info->trash_lst, exe);
	else if (ft_strncmp("export", builtin, ft_strlen(builtin)) == 0)
		i = export_minishell(info, *(exe->cmd_n_arg + 1));
	else if (ft_strncmp("pwd", builtin, ft_strlen(builtin)) == 0)
		pwd_minishell(info);
	else if (ft_strncmp("unset", builtin, ft_strlen(builtin)) == 0)
		i = unset_minishell(info, *(exe->cmd_n_arg + 1));
}

int	is_builtins(char *cmd, char **built_lst)
{
	int	i;

	i = 0;
	while (built_lst[i])
	{
		if (ft_strncmp(cmd, built_lst[i], ft_strlen(built_lst[i])) == 0)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

void	launch(t_pipe *pip, t_shell *shell_info, t_exe *exe, int i)
{
	if (is_builtins(exe->tab_cmd[i], exe->builtins) == 1)
	{
		if (i % 2 == 0)
		{
			builtins_0(pip, exe, shell_info);
		}
		else
		{
			builtins_1(pip, exe, shell_info);
		}
	}
	if (is_builtins(exe->tab_cmd[i], exe->builtins) == 0 || !exe->tab_cmd[i])
	{
		if (i % 2 == 0)
		{
			child_0(pip, exe, shell_info, exe->tab_cmd[i]);
		}
		else
		{
			child_1(pip, exe, shell_info, exe->tab_cmd[i]);
		}
	}
}
