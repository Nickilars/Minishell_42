/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:49:17 by nrossel           #+#    #+#             */
/*   Updated: 2023/09/01 15:33:43 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* -------------------- 1.Change directorie ft -------------------- */
static void	change_dir(char *cwd, char *new_cwd)
{
	int	ret;

	ret = chdir(new_cwd);
	if (ret == -1)
		ft_error_msg(1, new_cwd, "cd", 2);
	else
		getcwd(cwd, 1024);
}

/* -------------------- 2.Cd with "-" --------------------*/
static void	go_to_oldpwd(t_shell *info)
{
	t_list	*old_pwd;

	old_pwd = find_var_env(info->env, "OLDPWD");
	if (!old_pwd)
	{
		ft_error_msg(1, NULL, "cd", 4);
		return ;
	}
	change_dir(info->cwd, old_pwd->valeur);
	printf("%s\n", old_pwd->valeur);
}

/* -------------------- 2.Cd with args -------------------- */
static void	cd_with_args(t_shell *info, t_dlist **trash, char *arg)
{
	char		**tab;
	char		*path;
	struct stat	filestat;

	path = NULL;
	tab = ft_split(arg, ' ', trash);
	if (*arg == '\"')
			arg = ft_strtrim(arg, "\"", trash);
	if (**tab != '/')
		path = ft_strjoin(info->cwd, "/", trash);
	stat(ft_strjoin(path, *tab, trash), &filestat);
	if (ft_strncmp(*tab, "-", 2) == 0)
		go_to_oldpwd(info);
	else if (S_ISREG(filestat.st_mode))
		ft_error_msg(1, *tab, "cd", 1);
	else if (S_ISDIR(filestat.st_mode))
		change_dir(info->cwd, *tab);
	else
		ft_error_msg(1, *tab, "cd", 2);
}

/* -------------------- 2.Cd without args -------------------- */
static void	go_home(t_shell *info)
{
	char	*path_home_2;
	t_list	*path;

	path = find_var_env(info->env, "HOME");
	if (!path)
	{
		ft_error_msg(1, NULL, "cd", 3);
		return ;
	}
	path_home_2 = path->valeur;
	chdir(path_home_2);
	getcwd(info->cwd, 1024);
}

/* -------------------- 3.Cd main function -------------------- */
void	cd_minishell(t_shell *info, char *arg)
{
	if (!arg)
		go_home(info);
	else
		cd_with_args(info, &info->trash_lst, arg);
}
