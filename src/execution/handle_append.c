/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:50:40 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 10:50:41 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_append_files(char **tab_app_out, t_exe *exe);
static char	*find_last_element(char **tab_app_out);

void	handle_append(t_exe *exe)
{
	char	*last_element;
	char	**tab_app_out;

	tab_app_out = ft_split(exe->append[exe->idx], ' ', &exe->trash_x);
	create_append_files(tab_app_out, exe);
	last_element = find_last_element(tab_app_out);
	if (ft_strncmp("A_", last_element, 2) == 0)
	{
		last_element = (last_element + 2);
		exe->last_append = last_element;
	}
	else
	{
		exe->last_append = NULL;
	}
}

static char	*find_last_element(char **tab_app_out)
{
	int	i;

	i = 0;
	while (tab_app_out[i])
		i++;
	i--;
	return (tab_app_out[i]);
}

static void	create_append_files(char **tab_app_out, t_exe *exe)
{
	int	i;
	int	app;

	i = 0;
	while (tab_app_out[i])
	{
		if (ft_strncmp("A_", tab_app_out[i], 2) == 0)
		{
			app = open(&tab_app_out[i][2], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (app == -1)
				write(2, "error append file ing\n", 26);
			if (close(app) == -1)
				perror_msg_system(6, exe);
		}
		i++;
	}
}
