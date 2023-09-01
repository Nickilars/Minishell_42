/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:52:28 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 13:10:36 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* -------------------- 1.If Here_Doc ----------------------------*/
int	is_here_doc(t_tok *token)
{
	t_tok	*ptr;

	if (!token)
		return (SUCCESS);
	ptr = token;
	while (ptr != NULL && ptr->next != NULL)
		ptr = ptr->next;
	if (ptr->type == H_D)
		return (ERROR);
	else if (!ptr->prev)
		return (SUCCESS);
	else if (ptr->type == SPACEE && ptr->prev->type == H_D)
		return (ERROR);
	return (SUCCESS);
}

/* -------------------- 2.If buff has $env_var ----------------------------*/
char	*if_env_var_word(char *str, t_dlist *env, t_dlist **trash)
{
	int		i;
	int		j;
	char	*tmp[3];
	t_list	*ret;

	i = 0;
	j = 0;
	tmp[0] = NULL;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (!ft_isparsing_char(str[i]) && ft_issigle(str[i])
		&& str[i])
	{
		while (ft_isprint(str[i + j])
			&& !ft_isparsing_char(str[i + j]))
			j++;
		tmp[1] = ft_substr(str + i, 0, j, trash);
	}
	tmp[2] = ft_substr(str, 0, i, trash);
	ret = find_var_env(env, tmp[2]);
	if (ret)
		tmp[0] = ft_strdup_pars(ret->valeur, trash);
	if (j > 0)
		tmp[0] = ft_strjoin(tmp[0], tmp[1], trash);
	return (tmp[0]);
}

/* -------------------- 3.If buff has $? ----------------------------*/
char	*if_errno_word(char *str, t_dlist **trash)
{
	int		i;
	char	*tmp[2];

	i = 0;
	if (!ft_isparsing_char(*str))
	{
		while (str[i] != '\0' && !ft_isparsing_char(str[i]))
			i++;
		tmp[1] = ft_substr(str, 0, i, trash);
	}
	tmp[0] = ft_strdup(ft_itoa(g_errno, trash), trash);
	if (i > 0)
		tmp[0] = ft_strjoin(tmp[0], tmp[1], trash);
	return (tmp[0]);
}

/* -------------------- 4.Strdup for special case ----------------------------*/
char	*ft_strdup_pars(const char *str, t_dlist **trash)
{
	int		i;
	int		len;
	char	*s_cpy;

	if (!str || !*str)
		return (NULL);
	i = 0;
	len = ft_strlen(str);
	s_cpy = my_malloc(len + 1, sizeof(char), trash);
	if (!s_cpy)
		return (SUCCESS);
	while (i <= len && str[i])
	{
		s_cpy[i] = str[i];
		i++;
	}
	s_cpy[i] = 0;
	return (s_cpy);
}

/* -------------------- 5.check Spec char on str ----------------------------*/
int	check_spec_char(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (SUCCESS);
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
		{
			if (str[i] == ';')
				return (ft_error_msg(1, NULL, "word", 1));
			else if (str[i] == '\\')
				return (ft_error_msg(1, NULL, "word", 2));
			else if (str[i] == '!')
				return (ft_error_msg(1, NULL, "word", 3));
			else if (str[i] == '&')
				return (ft_error_msg(1, NULL, "word", 4));
			else if (str[i] == '`')
				return (ft_error_msg(1, NULL, "word", 5));
		}
		i++;
	}
	return (SUCCESS);
}
