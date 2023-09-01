/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:51:50 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 13:10:18 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* -------------------- 1.If $env_var ----------------------------*/
static char	*if_env_var(char *str, t_dlist *env, t_dlist **trash)
{
	int		i;
	int		j;
	char	*tmp[3];
	t_list	*ret;

	i = 0;
	j = 0;
	tmp[0] = NULL;
	ret = NULL;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (str[i] != '\"' && ft_issigle(str[i])
		&& str[i])
	{
		while (str[i + j] != '\"' && str[i + j])
			j++;
		tmp[1] = ft_substr(str + i, 0, j, trash);
	}
	tmp[2] = ft_substr(str, 0, i, trash);
	ret = find_var_env(env, tmp[2]);
	if (ret)
		tmp[0] = ft_strdup(ret->valeur, trash);
	if (j > 0)
		tmp[0] = ft_strjoin(tmp[0], tmp[1], trash);
	return (tmp[0]);
}

/* -------------------- 2.If $ on d_quote ----------------------------*/
static char	*ft_quote_d(char *str, t_dlist *env, t_dlist **trash)
{
	int		i;
	char	*tmp[2];

	i = 0;
	tmp[0] = NULL;
	while (str[i] != '\"' && str[i] != '$')
		i++;
	if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '?'))
		tmp[0] = ft_substr(str, 0, i, trash);
	if (ft_isalnum(str[i + 1]))
	{
		tmp[1] = if_env_var(str + (i + 1), env, trash);
		tmp[0] = ft_strjoin(tmp[0], tmp[1], trash);
	}
	else if (str[i + 1] == '?')
	{
		tmp[1] = if_errno(str + (i + 2), trash);
		tmp[0] = ft_strjoin(tmp[0], tmp[1], trash);
	}
	return (tmp[0]);
}

/* -------------------- 3.Check_end ----------------------------*/
static void	check_end(char *tmp, char *str, t_shell *info)
{
	if (!tmp && info->check > 0)
		creat_and_add(tmp, NULL, D_QUOTE, info);
	else if (!tmp)
		creat_and_add(NULL, str, D_QUOTE, info);
	else
		creat_and_add(tmp, str, D_QUOTE, info);
}

/* -------------------- 4.Double quote function ----------------------------*/
char	*ft_dquote(char *str, t_shell *info)
{
	int		i;
	char	*tmp;

	i = 0;
	info->check = 0;
	tmp = NULL;
	while (str[++i] != '\"')
	{
		if (str[i] == '$' && (ft_isalpha(str[i + 1])
				|| str[i + 1] == '?') && info->check == 0)
		{
			tmp = ft_quote_d(str + 1, info->env, &info->trash_lst);
			info->check++;
		}
		else if (str[i] == '$' && info->check != 0)
			tmp = ft_quote_d(tmp, info->env, &info->trash_lst);
	}
	info->i = i;
	check_end(tmp, str, info);
	return (str + (i + 1));
}

/* -------------------- 5.Simple quote function ----------------------------*/
char	*ft_squote(char *str, t_shell *info)
{
	int		i;

	i = 1;
	while (str[i] != '\'')
		i++;
	info->i = i;
	creat_and_add(NULL, str, S_QUOTE, info);
	return (str + (i + 1));
}
