/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:49:25 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 13:09:45 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* ------------------------- 1.Print env ------------------------------*/
static void	print_env(t_dlist *env)
{
	t_list	*node;

	node = env->head;
	while (node != NULL)
	{
		if (env->head->if_var_env == 1)
			printf("%s=%s\n", node->variable, node->valeur);
		node = node->next;
	}
	g_errno = 0;
}

/* ------------------------- 2.Env avec args ------------------------------*/
static void	env_with_arg(t_shell *info, char **arg)
{
	if (ft_strncmp(*arg, "env", 4) == 0)
	{
		while (ft_strncmp(*arg, "env", 4) == 0 && *arg != NULL)
			arg++;
		if (*arg != NULL)
		{
			ft_error_msg(127, *arg, "env", 0);
			return ;
		}
		print_env(info->env);
		g_errno = 0;
	}
	else if (ft_strncmp(*arg, "/", 1) == 0 && access(*info->arg, F_OK))
	{
		if (access(*arg, W_OK) != 0)
			ft_error_msg(126, *arg, "env", 0);
	}
	else
		ft_error_msg(127, *arg, "env", 0);
}

/* ------------------------- 3.Fonction env ------------------------------*/
void	env_minishell(t_shell *info, char *arg)
{
	t_list	*node;
	char	**tab_arg;

	if (!info->env->head)
	{
		printf("No minishell environment\n");
		return ;
	}
	node = info->env->head;
	if (arg)
	{
		tab_arg = ft_split(arg, ' ', &info->trash_lst);
		env_with_arg(info, tab_arg);
	}
	else
	{
		while (node != NULL)
		{
			if (node->if_var_env == 1)
				printf("%s=%s\n", node->variable, node->valeur);
			node = node->next;
		}
		g_errno = 0;
	}
}
