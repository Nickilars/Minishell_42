/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:52:04 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 13:10:28 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h" 

/* -------------------- 1.Check if $ exist ----------------------------*/
static char	*ft_word_d(char *buffer, t_dlist *env, t_dlist **trash)
{
	int		i;
	char	*tmp[2];

	i = 0;
	tmp[0] = NULL;
	while (!ft_isparsing_char(buffer[i]) && buffer[i] != '$')
		i++;
	if (buffer[i] == '$' && (ft_isalnum(buffer[i + 1]) || buffer[i + 1] == '?'))
		tmp[0] = ft_substr(buffer, 0, i, trash);
	i++;
	if (ft_isalnum(buffer[i]) || buffer[i] == '_')
	{
		tmp[1] = if_env_var_word(buffer + i, env, trash);
		tmp[0] = ft_strjoin(tmp[0], tmp[1], trash);
	}
	else if (buffer[i] == '?')
	{
		tmp[1] = if_errno_word(buffer + (i + 1), trash);
		tmp[0] = ft_strjoin(tmp[0], tmp[1], trash);
	}
	return (tmp[0]);
}

/* -------------------- 2.Analys buffer ----------------------------*/
static char	*analys_buffer(char *ret, char *buffer, t_shell *info)
{
	int	plop;

	info->check = 0;
	while (!ft_isparsing_char(buffer[info->i]))
	{
		if (buffer[info->i] == '$' && buffer[info->i + 1] == '$')
			plop = 1;
		else if (buffer[info->i] == '$'
			&& !ft_isparsing_char(buffer[info->i + 1]
				&& info->check == 0))
		{
			ret = ft_word_d(buffer, info->env, &info->trash_lst);
			info->check++;
		}
		else if (buffer[info->i] == '$' && info->check != 0)
			ret = ft_word_d(ret, info->env, &info->trash_lst);
		info->i++;
	}
	return (ret);
}

/* -------------------- 3.Word function ----------------------------*/
char	*ft_word(char *buffer, t_shell *info)
{
	char	*tmp;

	info->i = 0;
	tmp = NULL;
	if (info->token && is_here_doc(info->token))
	{
		while (!ft_isparsing_char(buffer[info->i]))
			info->i++;
		creat_and_add(tmp, buffer, WORD, info);
	}
	else
		tmp = analys_buffer(tmp, buffer, info);
	if (!tmp && info->check > 0)
		creat_and_add(tmp, NULL, WORD, info);
	else if (!tmp)
		creat_and_add(NULL, buffer, WORD, info);
	else
		creat_and_add(tmp, buffer, WORD, info);
	return (buffer + info->i);
}
