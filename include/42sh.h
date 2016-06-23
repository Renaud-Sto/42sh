/*
** 42sh.h for 42sh in /home/gastal_r/rendu/42sh/NE_PAS_TOUCHER/include
**
** Made by
** Login   <gastal_r@epitech.net>
**
** Started on  Thu May 26 21:26:35 2016
** Last update	Fri Jun 03 15:19:57 2016 Full Name
*/

# ifndef		_42_SH_H_
# define		_42_SH_H_

#include		<stdlib.h>
#include		<unistd.h>
#include		<sys/types.h>
#include		<sys/stat.h>
#include		<sys/wait.h>
#include		<dirent.h>
#include		<fcntl.h>
#include		<signal.h>
#include		<stdio.h>

# define SEPARATOR	"&|;"

# define BLEUCLAIR	"\033[01;34m"
# define ROUGE		"\033[00;31m"
# define ROUGEFONCE     "\033[0;31m"
# define SOULIGNE	"\033[04m"
# define NORMAL		"\033[00m"
# define ROSE		"\033[1;31m"
# define VERTFONCE	"\033[0;32m"
# define VERTCLAIR	"\033[1;32m"
# define ORANGE		"\033[0;33m"
# define JAUNE		"\033[1;33m"
# define BLEU		"\033[00;34m"
# define BLEUFONCE	"\033[0;34m"
# define BLEURCLAIR	"\033[1;34m"
# define VIOLETFONCE	"\033[0;35m"
# define VIOLETCLAIR	"\033[1;35m"
# define CYANFONCE	"\033[0;36m"
# define CYANCLAIR	"\033[1;36m"

typedef struct		 s_list
{
  char			*name;
  char			*data;
  struct s_list		*prev;
  struct s_list		*next;
}			t_list;

typedef struct		s_alias
{
  char			*alias;
  char		        **cmd;
  struct s_alias	*next;
  struct s_alias	*prev;
}			t_alias;

typedef struct		s_alias_cmd
{
  char			*alias;
  char		        **cmd;
  struct s_alias_cmd	*next;
  struct s_alias_cmd	*prev;
}			t_alias_cmd;

typedef struct		s_history
{
  char			*cmd;
  int			ligne;
  struct s_history	*next;
  struct s_history	*prev;
}			t_history;

typedef struct		s_plist
{
  int			exit_value;
  t_list		*begin;
  t_list		*end;
  t_alias		*begin_a;
  t_alias		*end_a;
  t_alias_cmd		*begin_acmd;
  t_alias_cmd		*end_acmd;
  t_history		*begin_h;
  t_history		*end_h;
  int			size;
  int			pipe;
  char			*pwd_42;
}			t_plist;

typedef struct		s_cmd
{
  char			**cmd;
  struct s_cmd		*prev;
  struct s_cmd		*next;
}			t_cmd;

typedef struct		s_pcmd
{
  t_cmd			*begin;
  t_cmd			*end;
}			t_pcmd;

typedef struct		s_sep
{
  char			*sep;
  struct s_sep		*prev;
  struct s_sep		*next;
}			t_sep;

typedef struct		s_psep
{
  t_sep			*begin;
  t_sep			*end;
}			t_psep;

typedef struct		s_env
{
  char			**env;
}			t_env;

typedef struct		s_data
{
  int			i;
  int			j;
  int			tmp;
  char			*cmd1;
  char			*cmd2;
}			t_data;

void			my_putchar(char c);
void                    show_sep(t_psep *psep);
void                    show_cmd(t_pcmd *pcmd);
void                    add_sep(t_psep *list, char *buff);
void                    add_cmd(t_pcmd *list, char *buff);
char			**my_str_to_wordtab(char *str);
char                    **init_env(char **env, t_plist *plist);
char			*get_next_line(const int fd);
void			my_putstr(char *str);
int			my_strlen(char *str);
char			*my_strdup(char *str);
void                    env_to_list(t_plist *list, char *env);
int			echo(t_plist *plist, char **tab, char **env);
char			*my_strcat(char *, char *, int, int);
void			clear_list(t_plist *list);
char                    **list_to_env(t_list *tmp, t_list *list);
int                     pars_prompt(t_plist *plist, t_env *env, char *st);
int			my_getnbr(char *str);
int                     prompt(t_env *env, t_plist *plist);
void                    free_tab(char **env);
void                    free_prompt_list(t_pcmd *pcmd, t_psep *psep);
int                     init_prompt_list(t_pcmd *pcmd, t_psep *psep);
int                     init_list(t_plist *plist);
void                    free_list(t_plist *plist);
void			my_puts(char *str);
int			my_strcmp(char *, char *);
void			echo_valuenv(char **tab, t_list *list);
char                    **get_path(t_plist *plist);
char                    *test_access(t_plist *plist, char *cmd);
void                    free_path(char **path);
int			set_env(t_plist *plist, char **cmd, char **env);
int			show_list(t_plist *plist, char **cmd, char **env);
void                    act_pwd(t_plist *plist, char *path);
char                    *get_oldpwd(t_plist *plist);
 char                    *get_pwd(t_plist *plist);
void                    act_oldpwd(t_plist *plist, char *path);
int                     cd_tile(t_plist *plist, char *dir);
void                    cd_prec(t_plist *plist, char *path);
int                     cd_home(t_plist *plist);
int                     cd_dir(t_plist *plist, char *dir);
int                     cd_old(t_plist *plist);
char			*my_realloc(char *, int);
int                     cd_main(t_plist *plist, char **cmd, char **env);
int                     double_red_right(t_plist *plist, char **cmd,
					 char **env);
int                     red_right(t_plist *plist, char **cmd, char **env);
char                    **order_args(char **prompt, int i, int j);
int                     system_fonc(t_plist *plist, char **cmd, char **env);
int                     unset_env(t_plist *plist, char **cmd, char **env);
int                     red_right(t_plist *plist, char **cmd, char **env);
int                     red_left(t_plist *plist, char **cmd, char **env);
int                     double_red_left(t_plist *plist, char **cmd,
					char **env);
int			launch(t_env *env, t_plist *envlist,
			       t_cmd *tmp, t_sep *tmp_sep);
int			exec_fonc(t_plist *plist, char **cmd, char **env, int status);
char                    *pre_parsing(char *prompt, int i, int j);
int                     return_chdir(char *dir, char *newpath);
int                     check_dir(t_plist *plist, char *newpath, char *dir);
void                    add_alias(t_plist *list, char *alias, char *cmd);
char                    **test_alias(t_plist *plist, char **cmd);
void			cmd_to_history(t_plist *list, char *cmd);
void			show_history(t_plist *list);
void			clear_history(t_plist *list);
char			*clear_history_c(t_plist *list);
void			my_putnbr(int nbr);
int                     background(t_plist *plist, char **cmd, char **env);
int			add_alias_cmd(t_plist *list, char **tab,  char **env);
void			add_alias_cmd_list(t_plist *list, char *alias, char *cmd);
int			pop_list_alias(t_plist *list, int pos);
int			pop_alias_cmd(t_plist *list, char **tab,  char **env);
int			system_fonc_pipe(t_plist *plist, char **cmd, char **env);
int                     exec_fonc_pipe(char **cmd, char **env);
char			*check_cmd_history(t_plist *plist, char *st, int i, int j);
int			check_exist(t_plist *list, char *alias, char *cmd);
void			alias(t_plist *list);
char			*open_history(t_plist *list, int fd);
char			*add_to_history(t_plist *list);
void                    free_alias_cmd(t_plist *list);
int		        check_action(char **tab, char **env, t_plist *envlist);
int			pipe_inf(t_plist *plist, t_cmd *cmd, int n, char **env);
int			history_main(t_plist *plist, char **cmd, char **env);
int                     exit_end(t_plist *list, int i);
int                     show_alias(t_plist *list);
int			check_invalid_cmd();
int			sig_func_dad(int pid, int status);
void			print_sig(int status);
int                     print_command_not_found(char *cmd);
char                    **alias_arg(char **alias, char **cmd);
int                     launch_alias(t_plist *plist, char **buff, char **env);
void			init_history_path(t_plist *plist);
#endif			/* _42_SH_H_ */
