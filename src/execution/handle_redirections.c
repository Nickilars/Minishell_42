/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:50:58 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 10:50:59 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_outfile_append_redirections(t_exe *exe);
static char	**handle_infile(t_exe *exe);
static char	**handle_outfile(t_exe *exe);
static void	handle_infile_heredoc_redirections(t_exe *exe);
static void	handle_outfile_append_redirections(t_exe *exe);

void	handle_redirections(t_exe *exe, t_pipe *pipe)
{
	handle_infile_heredoc_redirections(exe);
	handle_outfile_append_redirections(exe);
	init_struc_pipe(pipe, exe->redi_infile[0], exe->red_out[0], exe);
}

static char	**handle_infile(t_exe *exe)
{
	int		i;
	int		in;
	char	**infile_tab;

	infile_tab = ft_split(exe->redi_infile[exe->idx], ' ', &exe->trash_x);
	i = 0;
	if (infile_tab[0])
	{
		while (infile_tab[i])
		{
			in = open(infile_tab[i], O_RDONLY, 0644);
			if (in == -1)
				perror_msg_system(7, exe);
			close(in);
			if (in == -1)
				perror_msg_system(6, exe);
			i++;
		}
		i--;
	}
	exe->redi_infile[0] = infile_tab[i];
	return (&exe->redi_infile[0]);
}

static char	**handle_outfile(t_exe *exe)
{
	int		i;
	int		out;
	char	**outfile_tab;

	outfile_tab = ft_split(exe->red_out[exe->idx], ' ', &exe->trash_x);
	i = 0;
	if (outfile_tab[0])
	{
		while (outfile_tab[i])
		{
			out = open(outfile_tab[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (out == -1)
				perror_msg_system(7, exe);
			close (out);
			if (out == -1)
				perror_msg_system(6, exe);
			i++;
		}
		i--;
	}
	exe->red_out[0] = outfile_tab[i];
	return (&exe->red_out[0]);
}

static void	handle_infile_heredoc_redirections(t_exe *exe)
{
	int	i;

	i = 0;
	if (exe->nb_of_valid_heredoc > 0)
	{
		if (exe->heredoc[exe->idx])
		{
			create_heredoc_tab(exe);
			while (exe->heredoc[i])
				i++;
			if (ft_strcmp(exe->heredoc[i - 1], exe->last_heredoc) == 0)
				exe->redi_infile[0] = ".heredoc.txt";
		}
	}
	else
	{
		if (exe->redi_infile[exe->idx] != NULL)
			exe->redi_infile = handle_infile(exe);
		else
			exe->redi_infile[0] = NULL;
	}
}

static void	handle_outfile_append_redirections(t_exe *exe)
{
	if (exe->red_out[exe->idx])
	{
		exe->red_out = handle_outfile(exe);
	}
	if (exe->append[exe->idx] && exe->last_append)
	{
		exe->red_out[0] = exe->last_append;
	}
	if (!exe->red_out[exe->idx] && !exe->append[exe->idx])
	{
		exe->red_out[0] = NULL;
	}
}
