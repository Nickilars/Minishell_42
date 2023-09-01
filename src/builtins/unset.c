/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:49:38 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 17:46:13 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* -------------------- 1.clear info node -------------------- */
static int	check_char(int index, char c)
{
	int	ret;

	ret = 0;
	if (index == 0)
	{
		if (!ft_isalpha(c) && c != '_')
			return (ERROR);
	}
	else
	{
		if (!ft_isalnum(c) && c != '_')
			return (ERROR);
	}
	return (SUCCESS);
}

/* -------------------- 1.clear info node -------------------- */
int	check_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (SUCCESS);
		if (check_char(i, str[i]))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

/* -------------------- 2.clear info node -------------------- */
static void	clear_node(t_shell *info, t_list *node)
{
	if (node->prev)
	{
		if (node->next)
		{
			node->next->prev = node->prev;
			node->prev->next = node->next;
		}
		else
		{
			node->prev->next = NULL;
			info->env->tail = node->prev;
		}
	}
	else if (node->next)
	{
		node->next->prev = NULL;
		info->env->head = node->next;
	}
	node->valeur = NULL;
	node->variable = NULL;
	node->next = NULL;
	node->prev = NULL;
	node = NULL;
	info->env->len--;
}

/* -------------------- 3.analyze arg unset ----------------------- */
static void	analyze_arg(char **tab, t_shell *info)
{
	int		i;
	t_list	*node;

	i = 0;
	while (tab[i])
	{
		if (check_str(tab[i]))
		{
			ft_error_msg(1, tab[i], "unset", 0);
			return ;
		}
		node = find_var_env(info->env, tab[i++]);
		if (node)
		{
			clear_node(info, node);
			if (info->env->len == 0)
				info->env->head = NULL;
		}
	}
}

/* -------------------- 4.Main function unset -------------------- */
int	unset_minishell(t_shell *info, char *arg)
{
	char	**tab;
	int		check;

	if (!arg || !*arg)
		return (SUCCESS);
	check = 0;
	tab = ft_split(arg, ' ', &info->trash_lst);
	if (tab)
		analyze_arg(tab, info);
	return (SUCCESS);
}
