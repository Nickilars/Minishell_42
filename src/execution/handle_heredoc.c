/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:50:51 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 10:50:52 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_signals(int num);
static void	set_heredoc_signals(void);
static void	create_and_fill_heredoc(char *buffer, t_exe *exe, char *heredoc);
static void	h_creation(char *buffer, char **heredoc, t_exe *exe, int size);

void	handle_heredoc(t_exe *exe)
{
	int		size;
	char	*buffer;
	char	**heredoc_tab;

	buffer = NULL;
	setup_terminal(0, exe);
	set_heredoc_signals();
	exe->str_heredoc = create_str_heredoc(exe->heredoc, exe);
	heredoc_tab = ft_split(exe->str_heredoc, ' ', &exe->trash_x);
	size = ft_tabsize(heredoc_tab);
	h_creation(buffer, heredoc_tab, exe, size);
	free(buffer);
	buffer = NULL;
	setup_terminal(1, exe);
}

static void	set_heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = heredoc_signals;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
}

static void	heredoc_signals(int num)
{
	if (num == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	if (num == SIGQUIT)
	{
		return ;
	}
}

static void	create_and_fill_heredoc(char *buffer, t_exe *exe, char *heredoc)
{
	int	size;
	int	fd;

	exe->last_heredoc = heredoc;
	fd = open(".heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd == -1)
		perror_msg_system(7, exe);
	while (ERROR)
	{
		buffer = readline("> ");
		size = ft_strlen(buffer);
		if (ft_strncmp(buffer, heredoc, ft_strlen(heredoc) + 1) == 0)
		{
			break ;
		}
		write(fd, buffer, size);
		write(fd, "\n", 1);
		free(buffer);
		buffer = NULL;
	}
	if (close(fd) == -1)
		perror_msg_system(6, exe);
	free(buffer);
	buffer = NULL;
}

static void	h_creation(char *buffer, char **heredoc, t_exe *exe, int size)
{
	int	i;

	i = 0;
	while (heredoc[i])
	{
		if (buffer)
		{
			if (ft_strncmp(buffer, heredoc[i],
					(ft_strlen(heredoc[i]) + 1)) == 0)
				i++;
			free(buffer);
			buffer = NULL;
		}
		if (i == size - 1)
		{
			create_and_fill_heredoc(buffer, exe, heredoc[i]);
			break ;
		}
		buffer = readline("> ");
	}
}
