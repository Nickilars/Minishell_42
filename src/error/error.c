/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:50:10 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 10:50:11 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* ----------------- 1. Error main function --------------------- */
int	ft_error_msg(int errn, char *str, char *ft, int num)
{
	(void) num;
	g_errno = errn;
	if (ft_strncmp(ft, "unset", 6) == 0)
		printf(""RED"minishell"RESET": unset: `%s': not a valid identifier\n",
			str);
	else if (ft_strncmp(ft, "exit", 5) == 0)
		error_exit(errn, str);
	else if (ft_strncmp(ft, "cd", 3) == 0)
		error_cd(errn, num, str);
	else if (ft_strncmp(ft, "env", 4) == 0)
		error_env(errn, str);
	else if (ft_strncmp(ft, "syntax", 7) == 0)
		error_syntax(errn, num, str);
	else if (ft_strncmp(ft, "word", 5) == 0)
		error_word(num);
	else if (ft_strncmp(ft, "export", 7) == 0)
		printf(""RED"minishell"RESET": export: `%s': not a valid identifier\n",
			str);
	return (ERROR);
}

/* ------------------- 2. Error msg & exit function ------------------------- */
void	exit_with_error_msg(char *str, t_dlist **trash, t_exe *exe)
{
	ft_error_msg(255, str, "exit", 0);
	exit_free_ft(trash, exe, 1, NULL);
}
