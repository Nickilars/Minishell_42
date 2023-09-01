/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:51:53 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 10:51:54 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*red_in(char *str, t_tok **lst, t_dlist **trash)
{
	t_tok	*token;

	if (ft_strncmp(str, "<<", 2) == 0)
	{
		token = new_node(ft_strdup("<<", trash), H_D, trash);
		tok_addlst(lst, token);
		return (str + 2);
	}
	else
	{
		token = new_node(ft_strdup("<", trash), RED_IN, trash);
		tok_addlst(lst, token);
		return (str + 1);
	}
}

char	*red_out(char *str, t_tok **lst, t_dlist **trash)
{
	t_tok	*token;

	if (ft_strncmp(str, ">>", 2) == 0)
	{
		token = new_node(ft_strdup(">>", trash), APPEND, trash);
		tok_addlst(lst, token);
		return (str + 2);
	}
	else
	{
		token = new_node(ft_strdup(">", trash), RED_OUT, trash);
		tok_addlst(lst, token);
		return (str + 1);
	}
}
