/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:49:31 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 17:46:09 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* -------------------------- 1.Print export -------------------------------*/
static void	print_export(char **var)
{
	int	i;
	int	j;

	i = -1;
	while (var[++i])
	{
		j = 0;
		printf("declare -x ");
		if (found_char(var[i], '='))
		{
			while (var[i][j] != '=')
				printf("%c", var[i][j++]);
			j++;
			printf("=\"");
			while (var[i][j])
				printf("%c", var[i][j++]);
			printf("\"\n");
		}
		else
		{
			while (var[i][j])
				printf("%c", var[i][j++]);
			printf("\n");
		}
	}
}

/* -------------------- 2. Tri apha tab -----------------------*/
static void	ft_trialpha(char **env)
{
	int		i;
	int		j;
	char	**var;

	i = 0;
	var = env;
	while (i < ft_tabsize(env))
	{
		j = 0;
		while (var[j])
		{
			if (var[j + 1] && ft_strcmp(var[j], var[j + 1]) > -1)
				ft_strswap(&var[j], &var[j + 1]);
			j++;
		}
		i++;
	}
	print_export(var);
}

/* -------------------- 3.Export without args -------------------------*/
static void	export_no_args(t_shell *info)
{
	char	**env;

	env = lst_to_tab(info->env, &info->trash_lst);
	ft_trialpha(env);
}

/* ------------------------- 4.Export with args ------------------------------*/
static void	export_with_args(t_shell *info, char **arg)
{
	t_list	*node;
	char	*tmp;
	int		i;

	i = 0;
	node = find_var_env(info->env, arg[i]);
	if (!node)
	{
		node = ft_dlst_newcontent(NULL, &info->trash_lst);
		str_to_node(arg[i], node, info, 1);
		ft_dlst_addback(&info->env, node);
	}
	else
	{
		if (found_char(arg[i], '='))
		{
			tmp = ft_strrchr(arg[i], '=');
			if (!node->valeur && !tmp)
				fill_node(node, node->variable,
					ft_strdup(tmp, &info->trash_lst), 1);
			else
				fill_node(node, node->variable,
					ft_strdup(tmp + 1, &info->trash_lst), 1);
		}
	}
}

/* ------------------------ 5.Main fonction export ---------------------------*/
int	export_minishell(t_shell *info, char *arg)
{
	char	**tab;
	int		i;

	i = 0;
	if (!arg)
	{
		export_no_args(info);
		return (SUCCESS);
	}
	else
	{
		tab = ft_split(arg, ' ', &info->trash_lst);
		while (tab[i])
		{
			if (check_str(tab[i]))
				ft_error_msg(1, tab[i], "export", 0);
			else
				export_with_args(info, tab + i);
			i++;
		}	
	}
	return (ERROR);
}
