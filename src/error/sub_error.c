/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:50:13 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/29 10:50:14 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* ---------------- 1. Exit errors ---------------- */
void	error_exit(int errn, char *str)
{
	if (errn == 1)
	{
		printf("exit\n");
		printf(""RED"minishell"RESET": exit: too many arguments\n");
	}
	else if (errn == 255)
	{
		printf("exit\n");
		printf(""RED"minishell"RESET": exit: %s: numeric argument required\n",
			str);
	}
}

/* ---------------- 2. Cd errors ---------------- */
void	error_cd(int errn, int num, char *str)
{
	if (errn == 1 && num == 1)
		printf(""RED"minishell"RESET": cd: %s: Not a directory\n", str);
	else if (errn == 1 && num == 2)
		printf(""RED"minishell"RESET": cd: %s: No such file or directory\n",
			str);
	else if (errn == 1 && num == 3)
		printf(""RED"Minishell"RESET": cd : HOME not set\n");
	else if (errn == 1 && num == 4)
		printf(""RED"Minishell"RESET": cd : OLDPWD not set\n");
}

/* ---------------- 3. Env errors ---------------- */
void	error_env(int errn, char *str)
{
	if (errn == 126)
		printf(""RED"env"RESET": %s: Premission denied\n", str);
	else if (errn == 127)
		printf(""RED"env"RESET": %s: No such file or directory\n", str);
}

/* ---------------- 4. Syntax errors ---------------- */
void	error_syntax(int errn, int num, char *str)
{
	printf(""RED"minishell"RESET"");
	if (errn == 1 && num == 0)
		printf(": %s: No such file or directory\n", str);
	else if (errn == 1 && num == 1)
		printf(": stdin: is a directory\n");
	else if (errn == 1 && num == 2)
		printf(": erreur lors de l'ouverture du fichier\n");
	else if (errn == 258 && num == 0)
		printf(": syntax error near unexpected token `newline\'\n");
	else if (errn == 258 && num == 1)
		printf(": syntax error near unexpected token `%s\'\n",
			str);
	else if (errn == 258 && num == 2)
		printf(": syntax error: unexpected end of file\n");
}

/* ---------------- 5. Word errors ---------------- */
void	error_word(int num)
{
	if (num == 1)
		printf(""RED"minishell"RESET": ';': Invalid special characters\n");
	else if (num == 2)
		printf(""RED"minishell"RESET": '\\': Invalid special characters\n");
	else if (num == 3)
		printf(""RED"minishell"RESET": '!': Invalid special characters\n");
	else if (num == 4)
		printf(""RED"minishell"RESET": '&': Invalid special characters\n");
	else
		printf(""RED"minishell"RESET": '`': Invalid special characters\n");
}
