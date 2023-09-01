/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:49:28 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 18:11:13 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* --------------------- 1. Check if alpha is in str ----------------------*/
static int	check_ll_min_max(char *str, t_dlist **trash, t_exe *exe)
{
	if (ft_strlen(str) <= 20)
	{
		if (ft_strlen(str) >= 19)
		{
			if (*str == '-' && ft_strlen(str) == 20)
			{
				if (ft_strncmp("-9223372036854775808", str, 21) < 0)
					exit_with_error_msg(str, trash, exe);
			}
			else if (ft_strlen(str) == 19)
			{
				if (ft_strncmp("9223372036854775807", str, 20) < 0)
					exit_with_error_msg(str, trash, exe);
			}
		}
	}
	else
		exit_with_error_msg(str, trash, exe);
	return (ERROR);
}

/* --------------------- 2. Check if str has only space ----------------------*/
static int	ft_isonlyspace(char *str)
{
	int	len_max;

	len_max = ft_strlen(str);
	while (*str)
	{
		if (*str == ' ')
			len_max--;
		str++;
	}
	if (len_max > 0)
		return (SUCCESS);
	return (ERROR);
}

/* --------------------- 3. Check if alpha is in str ----------------------*/
static int	check_digitchar(char *str, t_dlist **trash, t_exe *exe)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '-' || str[i] == '+') && ft_isdigit(str[i + 1]))
			i++;
		if (!ft_isdigit(str[i]))
		{
			ft_error_msg(255, str, "exit", 0);
			exit_free_ft(trash, exe, 1, NULL);
		}
		i++;
	}
	return (SUCCESS);
}

/* ---------------------- 4. Check if str is "--" ------------------------*/
static int	check_line(char **arg, t_dlist **trash, t_exe *exe)
{
	if (!arg)
		exit (g_errno);
	if (!*arg)
		ft_error_msg(255, *(arg - 1), "exit", 0);
	else if (!ft_isdigit(**arg))
		ft_error_msg(255, *arg, "exit", 0);
	else
	{
		check_digitchar(*arg, trash, exe);
		if (*(arg + 1) != NULL)
			ft_error_msg(1, NULL, "exit", 0);
		else
		{
			printf("exit\n");
			exit_free_ft(trash, exe, 2, *arg);
		}
	}
	return (SUCCESS);
}

/* ------------------------- 5. Main fonction exit ------------------------*/
int	exit_minishell(char *arg, t_dlist **trash, t_exe *exe)
{
	char	**tab;
	char	*s_tmp;

	if (!arg)
		exit_free_ft(trash, exe, 1, NULL);
	if (*arg == '\"')
			arg = ft_strtrim(arg, "\"", trash);
	if (ft_isonlyspace(arg))
		return (ft_error_msg(255, arg, "exit", 0));
	s_tmp = ft_strtrim(arg, " ", trash);
	tab = ft_split(s_tmp, ' ', trash);
	if (!tab)
		exit (g_errno);
	else if (ft_strncmp(*tab, "--", 3) == 0)
		check_line(tab + 1, trash, exe);
	else
	{
		check_digitchar(*tab, trash, exe);
		check_ll_min_max(*tab, trash, exe);
		if (*(tab + 1) != NULL)
			return (ft_error_msg(1, NULL, "exit", 0));
		printf("exit\n");
		exit_free_ft(trash, exe, 2, *tab);
	}
	return (SUCCESS);
}
