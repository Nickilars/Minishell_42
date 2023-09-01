/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:51:32 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 10:51:33 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* ------------- 1.New token node ------------- */
t_tok	*new_node(char *str, int token, t_dlist **trash)
{
	t_tok	*new;

	new = my_malloc(1, sizeof(t_tok), trash);
	if (!new)
		return (NULL);
	if (!str)
		new->tok = NULL;
	else
		new->tok = str;
	new->type = token;
	new->next = 0;
	new->prev = 0;
	new->len = 0;
	return (new);
}

/* ------------- 2.Last tok lst ------------- */
t_tok	*tok_lastnode(t_tok *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
