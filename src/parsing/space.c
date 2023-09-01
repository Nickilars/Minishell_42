/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:51:57 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 10:51:58 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* ----------------- 1.Space function ----------------- */
char	*ft_space(char *str, t_tok **lst, t_dlist **trash)
{
	int		i;
	t_tok	*token;

	i = 0;
	while ((str[i] == ' ' || str[i] == '\t') && str[i] != '\0')
		i++;
	token = new_node(ft_strdup(" ", trash), SPACEE, trash);
	tok_addlst(lst, token);
	return (str + i);
}
