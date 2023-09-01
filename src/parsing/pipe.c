/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:51:46 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 10:51:47 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_pipe(char *str, t_tok **lst, t_dlist **trash)
{
	t_tok	*token;

	token = new_node(ft_strdup("|", trash), PIPE, trash);
	tok_addlst(lst, token);
	return (str + 1);
}
