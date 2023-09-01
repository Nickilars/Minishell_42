/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:51:29 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 13:10:05 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* ------------- 1. Str to node ------------- */
void	str_to_node(char *str, t_list *node, t_shell *info, int first_time)
{
	char	**tab;
	int		egal;
	t_list	*tmp;

	tmp = NULL;
	egal = found_char(str, '=');
	if (egal > 0)
	{
		tab = split_arg(str, egal, &info->trash_lst);
		if (!first_time)
			tmp = find_var_env(info->env, tab[0]);
		if (!tmp)
			fill_node(node, ft_strdup(tab[0], &info->trash_lst),
				ft_strdup(tab[1], &info->trash_lst), 1);
		else
			fill_node(tmp, ft_strdup(tab[0], &info->trash_lst),
				ft_strdup(tab[1], &info->trash_lst), 1);
	}
	else
		fill_node(node, ft_strdup(str, &info->trash_lst), NULL, 0);
}

/* ------------- 2. Fill node ------------- */
void	fill_node(t_list *node, char *s1, char *s2, int if_var)
{
	node->variable = s1;
	node->valeur = s2;
	node->if_var_env = if_var;
}

/* ------------- 3.Find Variable env. ------------- */
t_list	*find_var_env(t_dlist *env, char *var)
{
	t_list	*node;

	if (env->len == 0)
		return (NULL);
	node = env->head;
	while (node != NULL)
	{
		if (ft_strncmp(var, node->variable,
				ft_strlen(node->variable)) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

/* ------------- 4.list "env" to tab ------------- */
char	**lst_to_tab(t_dlist *lst, t_dlist **trash)
{
	char		**tab;
	t_list		*node;
	size_t		i;

	tab = my_malloc((lst->len + 1), sizeof(char *), trash);
	if (!tab)
		return (NULL);
	node = lst->head;
	i = 0;
	while (node != NULL && node->variable != NULL)
	{
		if (node->valeur)
		{
			tab[i] = ft_strjoin(node->variable, "=", trash);
			tab[i] = ft_strjoin(tab[i], node->valeur, trash);
		}
		else if (!node->valeur && ft_isupper(*node->variable))
			tab[i] = ft_strjoin(node->variable, "=", trash);
		else
			tab[i] = ft_strdup(node->variable, trash);
		i++;
		node = node->next;
	}
	return (tab);
}

/* ------------- 5. Tab to list ------------- */
void	tab_to_lst(t_shell *info, char **envp)
{
	int		i;
	t_list	*node;

	i = 0;
	while (envp[i])
	{
		node = ft_dlst_newcontent(NULL, &info->trash_lst);
		str_to_node(envp[i], node, info, 1);
		ft_dlst_addback(&info->env, node);
		node = NULL;
		i++;
	}
}
