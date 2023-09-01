/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:51:42 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 10:51:43 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* ---------- 1.Fill exec tab with token args ---------- */
static char	*fill_tab(char *tab, char *token, t_dlist **trash)
{
	if (!tab)
		tab = ft_strdup(token, trash);
	else
	{
		tab = ft_strjoin(tab, " ", trash);
		tab = ft_strjoin(tab, token, trash);
	}
	return (tab);
}

/* ---------- 2.If token type is out or append ---------- */
static void	out_or_append(t_tok *lst, t_exe *exec, int type, int index)
{
	char	*tmp;

	tmp = NULL;
	if (type == RED_OUT)
	{
		tmp = ft_strjoin("O_", lst->tok, &exec->trash_x);
		exec->append[index] = fill_tab(exec->append[index],
				tmp, &exec->trash_x);
		exec->red_out[index] = fill_tab(exec->red_out[index],
				lst->tok, &exec->trash_x);
	}
	else
	{
		tmp = ft_strjoin("A_", lst->tok, &exec->trash_x);
		exec->append[index] = fill_tab(exec->append[index],
				tmp, &exec->trash_x);
	}
}

/* ---------- 3.Sort token to exec tab ---------- */
static t_tok	*send_red(t_tok *lst, t_exe *exec, int type, int index)
{
	if (ft_isword(type))
		exec->tab_cmd[index] = fill_tab(exec->tab_cmd[index],
				lst->tok, &exec->trash_x);
	else
	{
		lst = lst->next;
		if (lst->type == SPACEE)
			lst = lst->next;
		if (type == RED_IN)
			exec->redi_infile[index] = fill_tab(exec->redi_infile[index],
					lst->tok, &exec->trash_x);
		else if (type == RED_OUT || type == APPEND)
			out_or_append(lst, exec, type, index);
		else if (type == H_D)
		{
			exec->heredoc[index] = fill_tab(exec->heredoc[index],
					lst->tok, &exec->trash_x);
			lst = lst->next;
		}
	}
	return (lst);
}

/* ---------- 4.Function that bridges parsing and execution ---------- */
void	pars_to_exec(t_shell *info, t_exe *exec)
{
	int		pipe;
	t_tok	*tmp;

	pipe = 0;
	tmp = info->token;
	while (tmp)
	{
		if (tmp->type == RED_IN)
			tmp = send_red(tmp, exec, RED_IN, pipe);
		else if (tmp->type == RED_OUT)
			tmp = send_red(tmp, exec, RED_OUT, pipe);
		else if (tmp->type == APPEND)
			tmp = send_red(tmp, exec, APPEND, pipe);
		else if (tmp->type == H_D)
			tmp = send_red(tmp, exec, H_D, pipe);
		else if (ft_isword(tmp->type))
			tmp = send_red(tmp, exec, WORD, pipe);
		if (!tmp)
			break ;
		if (tmp->type == PIPE)
			pipe++;
		tmp = tmp->next;
	}
	exec->nb_of_pipes = pipe;
}
