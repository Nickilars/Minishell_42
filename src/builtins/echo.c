/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:49:21 by nrossel           #+#    #+#             */
/*   Updated: 2023/09/01 10:24:50 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* -------------------- 1.Echo with -n option or not -----------------------*/
static void	print_echo(char **tab, char *str, int option_n)
{
	int		i;

	i = 0;
	if (!*tab & !str)
		return ;
	if (option_n == 1)
	{
		if (!*tab)
			return ;
		else
		{
			while (tab[i])
			{
				printf("%s", tab[i]);
				if (tab[i + 1])
					printf(" ");
				i++;
			}
		}
	}
	else
		printf("%s\n", str);
}

/* -------------------- 2. Check -n variant -----------------------*/
static int	check_n(char **tab)
{
	int	check;
	int	i;
	int	j;

	check = 0;
	i = 0;
	while (ft_strncmp(tab[i], "-n", 2) == 0)
	{
		if (ft_strncmp(tab[i], "-n", 3))
		{
			j = 2;
			while (tab[i][j] == 'n')
				j++;
			if (tab[i][j] != '\0' && ft_isprint(tab[i][j]))
				return (i);
		}
		i++;
	}
	return (i);
}

/* -------------------- 3. Echo main function -----------------------*/
void	echo_minishell(char *str, t_dlist **trash)
{
	int		check;
	char	**tmp;

	check = 0;
	if (!str || *str == '\0')
		printf("\n");
	else
	{
		tmp = ft_split(str, ' ', trash);
		if (!tmp)
		{
			printf("\n");
			return ;
		}
		check = check_n(tmp);
		if (check > 0)
			print_echo(tmp + check, str, 1);
		else
			print_echo(tmp, str, 0);
	}
}
