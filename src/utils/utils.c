/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:52:35 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 10:52:36 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* ---------------------- 1.Recherche de char ----------------------------*/
int	found_char(const char *str, int c)
{
	char	*cpy_str;
	int		i;

	if (!str || !*str)
	{
		return (-1);
	}
	cpy_str = (char *)str;
	i = 0;
	while (*cpy_str)
	{
		if (*cpy_str == c)
			i++;
		cpy_str++;
	}
	return (i);
}

/* ---------------------- 2.Swap ptr str ----------------------------*/
void	ft_strswap(char **s1, char **s2)
{
	char	*tmp;

	tmp = NULL;
	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

/* ---------------------- 3.Tab Len ----------------------------*/
int	ft_tabsize(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

/* ---------------------- 4.Initialisation ----------------------------*/
void	init_shell(t_shell *info, t_exe *exec, char **envp)
{
	if (getcwd(info->cwd, 1024) == NULL)
	{
		ft_putendl_fd("getcwd() error", 2);
		g_errno = 1;
	}
	info->check = 0;
	info->token = NULL;
	info->trash_lst = ft_calloc(1, sizeof(t_dlist));
	exec->trash_x = info->trash_lst;
	info->env = ft_dlst_new(&info->trash_lst);
	tab_to_lst(info, envp);
	exec->env_cpy = envp;
	exec->cmd_number = 0;
	exec->idx = 0;
	exec->nb_of_valid_heredoc = 0;
	exec->nb_probable_of_heredocs = 0;
	exec->tab_cmd = ft_calloc(1000, sizeof(char *));
	exec->heredoc = ft_calloc(1000, sizeof(char *));
	exec->redi_infile = ft_calloc(1000, sizeof(char *));
	exec->red_out = ft_calloc(1000, sizeof(char *));
	exec->append = ft_calloc(1000, sizeof(char *));
}

/* ---------------------- 5.Reset tab ----------------------------*/
void	ft_tabreset(char ***tab)
{
	int	i;

	i = 0;
	while ((*tab)[i])
	{
		(*tab)[i] = NULL;
		free((*tab)[i++]);
	}
	free(*tab);
}
