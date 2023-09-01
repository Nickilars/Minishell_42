/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:52:25 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 17:47:15 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* ------------------ 1.Reset all tab on exe ------------------ */
void	reset_shelltab(t_exe *exe)
{
	if (exe->tab_cmd)
	{
		ft_tabreset(&exe->tab_cmd);
		exe->tab_cmd = ft_calloc(1000, sizeof(char *));
	}
	if (exe->redi_infile)
	{
		ft_tabreset(&exe->redi_infile);
		exe->redi_infile = ft_calloc(1000, sizeof(char *));
	}
	if (exe->red_out)
	{
		ft_tabreset(&exe->red_out);
		exe->red_out = ft_calloc(1000, sizeof(char *));
	}
	if (exe->heredoc)
	{
		ft_tabreset(&exe->heredoc);
		exe->heredoc = ft_calloc(1000, sizeof(char *));
	}
	if (exe->append)
	{
		ft_tabreset(&exe->append);
		exe->append = ft_calloc(1000, sizeof(char *));
	}
}

/* ------------------ 2.Variable split ------------------ */
char	**split_arg(char *str, int egal, t_dlist **trash)
{
	char	**tab;

	if (egal == 1)
		tab = ft_split(str, '=', trash);
	else
		tab = ft_split_var(str, trash);
	return (tab);
}

/* ------------------ 3.Tab --> string ------------------ */
char	*tab_to_str(char **tab, t_dlist **trash)
{
	char	*str;
	int		i;

	if (!*tab)
		return (NULL);
	i = 1;
	str = *tab;
	while (tab[i])
	{
		str = ft_strjoin(str, " ", trash);
		str = ft_strjoin(str, tab[i++], trash);
	}
	return (str);
}

/* ------------------ 4.Remove quote ------------------ */
void	remove_quote(char *str, char quote)
{
	int	len;
	int	read;
	int	write;

	if (!str || !*str)
		return ;
	len = ft_strlen(str);
	read = 0;
	write = 0;
	if (*str == quote)
	{
		while (read < len)
		{
			if (str[read] != quote)
			{
				str[write] = str[read];
				write++;
			}
			read++;
		}
		str[write] = '\0';
	}
}

/* ------------------ 5.Type is sep ------------------ */
int	type_is_sep(int type)
{
	if (type == PIPE || type == RED_IN || type == RED_OUT
		|| type == APPEND || type == H_D)
		return (ERROR);
	return (SUCCESS);
}
