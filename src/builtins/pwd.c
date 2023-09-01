/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:49:35 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 10:49:36 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pwd_minishell(t_shell *info)
{
	if (getcwd(info->cwd, sizeof(info->cwd)) != NULL)
		printf("%s\n", info->cwd);
	else
	{
		ft_putendl_fd("getcwd() error", 2);
		g_errno = 1;
	}
}
