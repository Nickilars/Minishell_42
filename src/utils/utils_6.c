/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:52:31 by nrossel           #+#    #+#             */
/*   Updated: 2023/09/01 11:48:44 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* ---------------- 1.free function ---------------- */
void	exit_free_ft(t_dlist **trash, t_exe *exe, int exit_shell, char *err)
{
	long long	erno;

	if (err)
		erno = ft_atoll(err);
	ft_dlst_clear(trash, free);
	free(exe->red_out);
	free(exe->redi_infile);
	free(exe->heredoc);
	free(exe->tab_cmd);
	free(exe->append);
	if (exit_shell > 0)
		setup_terminal(1, exe);
	if (exit_shell == 1)
		exit (g_errno);
	else if (exit_shell == 2)
		exit (erno);
	else if (exit_shell == 3)
		exit (ERROR);
	else
		return ;
}

/* ---------------- 2. New dreadline in syntax ---------------- */
int	readline_syntax(t_tok *node, t_shell *info)
{
	char	*buff;

	while (1)
	{
		buff = readline(""GREEN"->"RESET" ");
		if (buff && *buff != '\0')
			break ;
		if (!buff)
			return (ft_error_msg(258, node->tok, "syntax", 2));
		free(buff);
	}
	add_history(buff);
	ft_char_sort(buff, info);
	free(buff);
	return (SUCCESS);
}

/* ---------------- 3. Check if arg is file or dir ---------------- */
int	check_path_redin(t_shell *info, t_tok *node, t_dlist **trash)
{
	char		*path;
	struct stat	filestat;

	path = ft_strjoin(info->cwd, "/", trash);
	stat(ft_strjoin(path, node->tok, trash), &filestat);
	if (S_ISDIR(filestat.st_mode))
		return (ft_error_msg(1, node->tok, "syntax", 1));
	else if (!S_ISREG(filestat.st_mode))
		return (ft_error_msg(1, node->tok, "syntax", 0));
	if (open(node->tok, O_RDWR) < 0)
		return (ft_error_msg(1, node->tok, "syntax", 2));
	return (SUCCESS);
}

/* ---------------- 4. Check if type si in or out ---------------- */
int	in_or_out(t_tok **lst, t_tok *node, t_shell *info)
{
	if ((*lst)->type == RED_IN)
	{
		if (check_path_redin(info, node, &info->trash_lst))
			return (ERROR);
	}
	else
		if (ft_strncmp((*lst)->tok, ">", 2) == 0)
			if (open(node->tok, O_WRONLY | O_CREAT | O_TRUNC, 0644) < 0)
				return (ft_error_msg(1, node->tok, "syntax", 2));
	(*lst) = node->next;
	return (SUCCESS);
}

/* -------------------- 5.If str is $? ----------------------------*/
char	*if_errno(char *str, t_dlist **trash)
{
	int		i;
	char	*tmp[2];

	i = 0;
	if (*str && *str != '\"')
	{
		while (!ft_isquote(str[i]) && str[i])
			i++;
		tmp[1] = ft_substr(str, 0, i, trash);
	}
	tmp[0] = ft_strdup(ft_itoa(g_errno, trash), trash);
	if (i > 0)
		tmp[0] = ft_strjoin(tmp[0], tmp[1], trash);
	return (tmp[0]);
}
