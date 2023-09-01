/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:50:37 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 10:50:38 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_start(t_exe *exe)
{
	exe->nb_probable_of_heredocs = exe->nb_of_pipes + 1;
	exe->nb_of_valid_heredoc = number_of_valid_heredoc(exe);
	if (exe->nb_of_valid_heredoc > 0)
		handle_heredoc(exe);
}

void	create_heredoc_tab(t_exe *exe)
{
	char	**heredoc_tab;

	heredoc_tab = ft_split(exe->heredoc[exe->idx], ' ', &exe->trash_x);
	exe->heredoc = heredoc_tab;
}

int	number_of_valid_heredoc(t_exe *exe)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (i <= exe->nb_probable_of_heredocs)
	{
		if (exe->heredoc[i] != NULL)
			size++;
		i++;
	}
	return (size);
}

char	*create_str_heredoc(char **exe_heredoc, t_exe *exe)
{
	char	*result;
	int		i;

	i = 0;
	result = my_malloc(100, sizeof(char *), &exe->trash_x);
	while (i <= exe->nb_probable_of_heredocs)
	{
		if (exe->heredoc[i] == NULL && i < exe->nb_probable_of_heredocs)
			i++;
		if (exe->heredoc[i])
			result = ft_strcat_heredoc(result, exe_heredoc[i], 0);
		i++;
	}
	return (result);
}
