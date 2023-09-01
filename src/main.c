/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:43:18 by nrossel           #+#    #+#             */
/*   Updated: 2023/09/01 14:18:09 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* -------------------- 1.Check validity parsing ----------------------------*/
static char	*purify_buffer(char *buff, t_dlist **trash)
{
	char	*tmp;

	tmp = ft_strtrim(buff, " \r\n\t\f\v", trash);
	free(buff);
	return (tmp);
}

/* -------------------- 1.Check validity parsing ----------------------------*/
static char	*ft_readline(t_shell *parse, t_exe *exec)
{
	char		*buffer;
	static char	*old_buffer;
	char		*tmp;

	buffer = readline(""BLUE"Minishell"GREEN">"RESET" ");
	setup_terminal(1, exec);
	if (!buffer)
		exit_free_ft(&parse->trash_lst, exec, 2, "0");
	tmp = purify_buffer(buffer, &parse->trash_lst);
	if (tmp && *tmp)
	{
		if (ft_strncmp(tmp, old_buffer, ft_strlen(old_buffer)) != 0)
		{
			add_history(tmp);
			old_buffer = tmp;
		}
	}
	return (tmp);
}

/* -------------------- 1.Check validity parsing ----------------------------*/
static void	ft_check(int check, t_shell *parse, t_exe *exe)
{
	if (check == 0)
	{
		shell_execution(exe, parse);
		parse->token = NULL;
		reset_shelltab(exe);
	}
	else if (check == 1)
	{
		printf(""RED"Erreur"RESET": nombre quote invalide\n");
		parse->token = NULL;
	}
	else if (check == 2)
		parse->token = NULL;
}

/* -------------------- 2.Main principale ----------------------------*/
int	main(int ac, char **av, char **envp)
{
	int			check;
	char		*buffer;
	t_shell		info_parse;
	t_exe		info_exe;

	(void) av;
	(void) ac;
	init_shell(&info_parse, &info_exe, envp);
	while (1)
	{
		setup_terminal(0, &info_exe);
		set_signals();
		rl_on_new_line();
		buffer = ft_readline(&info_parse, &info_exe);
		check = parse_shell (buffer, &info_parse, &info_exe);
		ft_check(check, &info_parse, &info_exe);
	}
	return (SUCCESS);
}
