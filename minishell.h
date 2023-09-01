/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:54:25 by nrossel           #+#    #+#             */
/*   Updated: 2023/09/01 10:58:28 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ----------- External libraries ----------- */

# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <curses.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <termios.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/resource.h>
# include <readline/history.h>
# include <readline/readline.h>

/* ----------- Internal libraries ----------- */

# include "./libft/include/libft.h"

/* ----------- Return value ----------- */

# define SUCCESS 0
# define ERROR 1

/* ----------- Colors code ----------- */

# define RESET "\033[0;39m"
# define GRAY "\033[0;90m"
# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[0;94m"
# define MAGENTA "\033[0;95m"
# define CYAN "\033[0;96m"
# define WHITE "\033[0;97m"

/* ----------- Global variable: Error number ----------- */

int	g_errno;

/* ----------- ENUM -> Type Token --------------- */

enum e_token
{
	WORD,
	S_QUOTE,
	D_QUOTE,
	RED_IN,
	RED_OUT,
	H_D,
	APPEND,
	SPACEE,
	PIPE
}	;

/*------------- Stucture token ------------*/

typedef struct s_tok
{
	int				len;
	char			*tok;
	enum e_token	type;
	struct s_tok	*next;
	struct s_tok	*prev;
}	t_tok;

/* ----------- Structure parsing --------------- */

typedef struct s_shell
{
	int				i;
	int				check;
	char			cwd[1024];
	char			**arg;
	t_dlist			*env;
	t_tok			*token;
	t_dlist			*trash_lst;
}	t_shell;

/*------------- Stucture executions ------------*/

typedef struct s_exec
{
	int				idx;
	struct termios	tp;
	struct termios	save;
	int				*save_pid;
	char			*builtins[8];
	char			**append;
	char			*last_append;
	char			*append_first_cmd;
	int				nb_of_pipes;
	int				nb_probable_of_heredocs;
	int				idx_doublon_append;
	int				nb_of_valid_heredoc;
	char			*last_heredoc;
	char			**tab_cmd;
	char			**cmd_n_arg;
	char			**env_cpy;
	char			*path;
	char			**access_path;
	char			*cmd_path;
	char			**redi_infile;
	char			**red_out;
	char			**heredoc;
	char			*str_heredoc;
	int				cmd_number;
	t_dlist			*trash_x;
	int				fd_out_backup;
	int				cmd_not_found;
}	t_exe;

typedef struct s_pipe
{
	int				fd_pipe1[2];
	int				fd_pipe2[2];
	int				fd_in;
	int				fd_out;
	char			*infile;
	char			*outfile;
	t_exe			exec_info;
}	t_pipe;

/* ---------------- Builtings ------------------ */

void		pwd_minishell(t_shell *info);
void		cd_minishell(t_shell *info, char *arg);
void		env_minishell(t_shell *info, char *arg);
int			unset_minishell(t_shell *info, char *arg);
void		echo_minishell(char *tab, t_dlist **trash);
int			export_minishell(t_shell *info, char *arg);
int			exit_minishell(char *arg, t_dlist **trash, t_exe *exe);

/* -------------- Fonctions principales -----------------------*/

int			parse_builtins(t_shell *info, t_exe *exec);
void		init_shell(t_shell *info, t_exe *exec, char **envp);
int			parse_shell(char *buff, t_shell *info, t_exe *exec);
int			shell_execution(t_exe *exe, t_shell *shell_info);

/* -------------- Fonctions parsing -----------------------*/

char		*ft_word(char *str, t_shell *info);
char		*ft_squote(char *str, t_shell *info);
char		*ft_dquote(char *str, t_shell *info);
int			ft_char_sort(char *buff, t_shell *info);
void		pars_to_exec(t_shell *info, t_exe *exec);
int			readline_syntax(t_tok *node, t_shell *info);
char		*red_in(char *str, t_tok **lst, t_dlist **trash);
char		*red_out(char *str, t_tok **lst, t_dlist **trash);
char		*ft_pipe(char *str, t_tok **lst, t_dlist **trash);
char		*ft_space(char *str, t_tok **lst, t_dlist **trash);
int			in_or_out(t_tok **lst, t_tok *node, t_shell *info);
int			check_syntax(t_shell *info, t_tok *lst, t_dlist **trash);
int			check_path_redin(t_shell *info, t_tok *node, t_dlist **trash);

/* -------------- Fonctions utilitaires -----------------------*/

int			ft_issigle(char c);
int			ft_isquote(char c);
int			check_str(char *str);
int			ft_isword(int token);
int			type_is_sep(int type);
int			ft_quotelen(char *str);
int			ft_tabsize(char **tab);
int			check_printchar(char c);
void		ft_tabreset(char ***tab);
int			is_here_doc(t_tok *token);
int			ft_isparsing_char(char c);
int			check_spec_char(char *str);
void		reset_shelltab(t_exe *exec);
void		ft_strswap(char **s1, char **s2);
int			found_char(const char *str, int c);
void		remove_quote(char *str, char quote);
int			ft_checkquote(char *str, int S_or_d);
char		*if_errno(char *str, t_dlist **trash);
char		*tab_to_str(char **tab, t_dlist **trash);
char		*if_errno_word(char *str, t_dlist **trash);
char		**ft_split_var(char *var, t_dlist **trash);
char		**split_arg(char *str, int egal, t_dlist **trash);
char		*ft_strdup_pars(const char *str, t_dlist **trash);
char		*if_env_var_word(char *str, t_dlist *env, t_dlist **trash);
void		exit_free_ft(t_dlist **trash, t_exe *exe,
				int exit_shell, char *err);

/* -------------- Fonctions utiles liste -----------------------*/

void		tok_clearlst(t_tok **lst);
t_tok		*tok_lastnode(t_tok *lst);
char		*ft_strdup_exec(char *str);
int			ft_lstsize_heredoc(t_list *lst);
void		display_node_heredoc(t_list *lst);
t_list		*find_var_env(t_dlist *env, char *var);
void		tok_addlst(t_tok **lst, t_tok *token);
void		tab_to_lst(t_shell *info, char **envp);
char		**lst_to_tab(t_dlist *lst, t_dlist **trash);
t_tok		*new_node(char *str, int token, t_dlist **trash);
char		**tokenlst_to_tab(t_tok *token, t_dlist **trash);
t_list		*ft_lstnew_heredoc(char *data, t_dlist **trash_lst);
void		display_lst_heredoc(t_list **ptr_to_head, char *name);
void		fill_node(t_list *node, char *s1, char *s2, int if_var);
void		strjoin_tok_node(t_tok *dest, t_tok *src, t_dlist **trash);
void		creat_and_add(char *tmp, char *str, int type, t_shell *info);
void		str_to_node(char *str, t_list *node, t_shell *info, int first_time);

/* -------------- Fonctions error -----------------------*/

void		error_word(int num);
void		error_env(int errn, char *str);
void		error_exit(int errn, char *str);
void		error_cd(int errn, int num, char *str);
void		error_syntax(int errn, int num, char *str);
int			ft_error_msg(int errno, char *str, char *ft, int num);
void		exit_with_error_msg(char *str, t_dlist **trash, t_exe *exe);

/* -------------- Fonctions test -----------------------*/
void		print_node(t_tok *node);
void		print_trash(t_dlist **trash);
void		test(char *str, char *fonction);
void		print_tab(char **tab, char *ft);
void		print_token(t_tok **lst, char *ft);
void		print_parsing(t_exe *exec, char *ft);
void		print_list(t_dlist *lst, char *ft, int info);

/* -------------- Fonctions d'execution ---------------------*/

void		save_pid(t_exe *exe, int pid);
void		fill_builtins_tab(t_exe *exe);
void		init_pipes_beginning(t_pipe *pip);
void		setup_pipes(t_pipe *pip, int process, t_exe *exe);
void		init_struc_pipe(t_pipe *d, char *infile, char *outfile, t_exe *exe);

void		handle_append(t_exe *exe);

void		heredoc_start(t_exe *exe);
void		handle_heredoc(t_exe *exe);
void		create_heredoc_tab(t_exe *exe);
int			number_of_valid_heredoc(t_exe *exe);
char		*ft_strcat_heredoc(char *dest, char *src, int end);
char		*create_str_heredoc(char **exe_heredoc, t_exe *exe);
char		**heredoc_data_saved(char *to_check, t_exe *exe, char *buffer);

void		close_pipes(t_pipe *d, int process);
void		setup_infile_cmd(t_pipe *pip, t_exe *exe);
void		handle_redirections(t_exe *exe, t_pipe *pipe);
void		setup_outfile_cmd(t_pipe *pip, t_exe *exe);

void		execution_no_pipe(t_exe *exe, t_pipe *pip, t_shell *shell_info);
void		execution_with_pipes(t_exe *exe, t_pipe *pip, t_shell *shell_info);

void		first_cmd(t_pipe *d, t_exe *exe);
char		*get_cmd_path(char *cmd, t_exe *exe);
void		last_cmd(t_pipe *d, int process, t_exe *exe);
void		middle_cmd(t_pipe *d, t_exe *exe, int process);
void		prepare_cmd(t_exe *exe, t_shell *d_shell, char *cmd);
void		setup_middle_cmd(t_pipe *pip, int option, t_exe *exe);

void		handle_dup_fd_single_cmd(t_pipe *pip, t_exe *exe);
void		single_cmd(t_pipe *pip, t_exe *exe, t_shell *d_shell, char *cmd);

int			is_builtins(char *cmd, char **built_lst);
void		builtins_1(t_pipe *d, t_exe *exe, t_shell *d_shell);
void		builtins_0(t_pipe *pip, t_exe *exe, t_shell *d_shell);
void		create_cmd_n_args_builtins(t_exe *exe, t_dlist **trash);
void		single_builtin(t_exe *exe, t_pipe *pip, t_shell *shell_info);
void		builtins_x(char *builtin, t_shell *info, char **cmd, t_exe *exe);

void		child_1(t_pipe *d, t_exe *exe, t_shell *d_shell, char *cmd);
void		child_0(t_pipe *pip, t_exe *exe, t_shell *d_shell, char *cmd);

void		launch(t_pipe *pip, t_shell *shell_info, t_exe *exe, int i);

void		command_not_found(char *cmd);
int			perror_msg_system(int errno, t_exe *exe);

char		*ft_strcpy(char *s1, char *s2);
char		**ft_split_exe(const char *str, char c, int var);
char		*strjoin_exec(char const *s1, char const *s2, t_exe *exe);

/*-----------------------------Signaux-----------------------------*/

void		set_signals(void);
void		signals_update(void);
void		sig_default(void);
void		handler_sg(int num);
void		handler_sg_update(int num);
void		setup_terminal(int mode, t_exe *exe);

#endif
