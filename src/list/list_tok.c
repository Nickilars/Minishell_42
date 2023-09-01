/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tok.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:51:23 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 10:51:24 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* ------------- 1.Add token node to lst ------------- */
void	tok_addlst(t_tok **lst, t_tok *token)
{
	t_tok	*ptr;

	ptr = *lst;
	if (!token)
		return ;
	if (!*lst)
	{
		*lst = token;
		token->len++;
		return ;
	}
	ptr->len++;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
		ptr->len++;
	}
	ptr->next = token;
	token->prev = ptr;
	token->len++;
}

/* ------------- 2.Clear token lst ------------- */
void	tok_clearlst(t_tok **lst)
{
	t_tok	*ptr;

	if (!*lst)
		return ;
	ptr = *lst;
	while (*lst != NULL)
	{
		ptr = (*lst)->next;
		free((*lst)->tok);
		free(*lst);
		*lst = ptr;
	}
}

/* ------------- 3.Len token lst ------------- */
static int	len_tokenlst(t_tok *token)
{
	int		i;
	t_tok	*tmp;

	if (!token)
		return (SUCCESS);
	i = 0;
	tmp = token;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

/* ------------- 4.lst token to **tab ------------- */
char	**tokenlst_to_tab(t_tok *token, t_dlist **trash)
{
	int		i;
	t_tok	*tmp;
	char	**tab;

	if (!token)
		return (NULL);
	i = len_tokenlst(token);
	tmp = token;
	tab = my_malloc((i + 1), (sizeof(char *)), trash);
	if (!tab)
		return (NULL);
	tab[i] = NULL;
	i = 0;
	while (tmp)
	{
		tab[i] = tmp->tok;
		i++;
		tmp = tmp->next;
	}
	return (tab);
}

/* ------------- 5.Join str node_tmp ------------- */
void	strjoin_tok_node(t_tok *dest, t_tok *src, t_dlist **trash)
{
	dest->tok = ft_strjoin(dest->tok, src->tok, trash);
	dest->next = src->next;
	src->next = NULL;
}
