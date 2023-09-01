/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:52:00 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 20:05:42 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* ----------------- 1.if token is pipe ----------------- */
static int	check_pipe(t_tok **node, t_shell *info)
{
	t_tok	*tmp;

	tmp = *node;
	*node = (*node)->next;
	if (!tmp->prev || tmp->prev->type == PIPE)
		return (ft_error_msg(258, tmp->tok, "syntax", 1));
	else if (tmp->prev->type == SPACEE)
	{
		if (type_is_sep(tmp->prev->prev->type))
			return (ft_error_msg(258, tmp->tok, "syntax", 1));
	}
	if (*node == NULL)
	{
		if (tmp->type == PIPE || (tmp->type == SPACEE
				&& tmp->prev->type == PIPE))
		{
			if (readline_syntax(tmp, info))
				return (ERROR);
		}
	}
	return (SUCCESS);
}

/* ----------------- 2.If token is in, out or append ----------------- */
static int	in_out_append(t_tok **node, t_shell *info)
{
	t_tok		*tmp;

	tmp = (*node)->next;
	if (!tmp || (tmp->type == SPACEE && !tmp->next))
		return (ft_error_msg(258, NULL, "syntax", 0));
	else if (tmp->type == SPACEE)
		tmp = tmp->next;
	if (!ft_isword(tmp->type) || !tmp->tok)
		return (ft_error_msg(258, tmp->tok, "syntax", 1));
	else if (ft_isword(tmp->type))
		if (in_or_out(node, tmp, info))
			return (ERROR);
	return (SUCCESS);
}

/* ----------------- 3.If token is heredoc ----------------- */
static int	heredoc(t_tok **node)
{
	t_tok	*tmp;

	tmp = (*node)->next;
	if (!tmp)
		return (ft_error_msg(258, NULL, "syntax", 0));
	else if (tmp->type == SPACEE)
		tmp = tmp->next;
	if (!tmp)
		return (ft_error_msg(258, NULL, "syntax", 0));
	else if (tmp->type != WORD)
		return (ft_error_msg(258, tmp->tok, "syntax", 1));
	(*node) = tmp->next;
	return (SUCCESS);
}

/* ----------------- 4.If token is quotes or word ----------------- */
static int	word(t_tok **current_node, t_tok *next_node, t_dlist **trash)
{
	if ((*current_node)->type == WORD && check_spec_char((*current_node)->tok))
		return (ERROR);
	if ((ft_isword((*current_node)->type) && next_node != NULL)
		&& ft_isword(next_node->type))
		strjoin_tok_node((*current_node), next_node, trash);
	else
		(*current_node) = next_node;
	return (SUCCESS);
}

/* ----------------- 5.Syntax ----------------- */
int	check_syntax(t_shell *info, t_tok *lst, t_dlist **trash)
{
	t_tok	*node;
	int		check;

	node = lst;
	check = 0;
	while (node != NULL)
	{
		if (node->type == PIPE)
			check = (check_pipe(&node, info));
		else if (node->type == RED_IN || node->type == RED_OUT
			|| node->type == APPEND)
			check = (in_out_append(&node, info));
		else if (node->type == H_D)
			check = (heredoc(&node));
		else if (ft_isword(node->type))
			check = word(&node, node->next, trash);
		else
			node = node->next;
		if (check > 0)
			return (ERROR);
	}
	return (SUCCESS);
}
