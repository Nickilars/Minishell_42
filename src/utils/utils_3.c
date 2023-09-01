/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:52:22 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 17:47:00 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* ---------------- 1.Check print char ---------------- */
int	check_printchar(char c)
{
	if (ft_isprint(c) && !ft_isquote(c))
		return (ERROR);
	return (SUCCESS);
}

/* ---------------- 2.Check char parsing ---------------- */
int	ft_isparsing_char(char c)
{
	if (ft_isquote(c) || c == '|' || c == '<'
		|| c == '>' || c == ' ' || c == '\0'
		|| c == '\t')
		return (ERROR);
	return (SUCCESS);
}

/* ---------------- 3.Check tok ---------------- */
int	ft_isword(int token)
{
	if (token == WORD || token == S_QUOTE
		|| token == D_QUOTE)
		return (ERROR);
	return (SUCCESS);
}

/* ---------------- 4.Len quote ---------------- */
int	ft_quotelen(char *s)
{
	int	i;

	i = 0;
	while (!ft_isquote(s[i]) && s[i])
		i++;
	return (i);
}

/* ---------------- 5.Check tok ---------------- */
void	creat_and_add(char *tmp, char *s, int type, t_shell *info)
{
	t_tok	*token;

	if (!tmp)
	{
		if ((type == S_QUOTE || type == D_QUOTE) && s)
			token = new_node(ft_substr(s, 1, info->i - 1,
						&info->trash_lst), type, &info->trash_lst);
		else if (type == WORD && s)
			token = new_node(ft_substr(s, 0, info->i, &info->trash_lst),
					type, &info->trash_lst);
		else if (((type == S_QUOTE || type == D_QUOTE || type == WORD)) && !s)
			token = new_node(NULL, type, &info->trash_lst);
		else
			token = new_node(ft_substr(s, 0, info->i, &info->trash_lst),
					type, &info->trash_lst);
	}
	else
		token = new_node(ft_strdup_pars(tmp, &info->trash_lst),
				type, &info->trash_lst);
	tok_addlst(&info->token, token);
}
