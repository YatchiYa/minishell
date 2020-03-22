
#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>
// # include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <dirent.h>
# include <stddef.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include "gnl/get_next_line.h"

# define IS_QUOTE(x) (x == '"' || x == '\'')

char	        **g_envv;
char            *oldpath;


void	        *ft_memalloc(size_t size);
char		    **ft_strsplit(char const *s, char c);
void	        ft_freestrarr(char **arr);
void	        exit_shell(void);
void			init_envv(int ac, char **av, char **envv);
void	        ft_putstr(char *str);
void	        ft_bzero(void *s, size_t n);
char	        *ft_strjoinch(char const *s1, char c);
int		        ft_strstartswith(char *s1, char *s2);
char	        *ft_strchr(const char *s, int c);
char	        *ft_strnew(size_t size);
void        	signal_handler(int signo);
void	        display_prompt_msg(void);
char        	*get_env_var(char *var);
void			parse_line(char *line);
char			**split_commande(char *line);
void    		handle_echo(char *str);
void			handle_pwd(void);
void			signal_handler2(int signo);
void		    handle_touch(char *str);
void		    handle_rm(char *str);
void			handle_cd(char *path);
void	        set_env_var(char *key, char *value);
char	        **realloc_envv(int new_size);
int		        find_env_var(char *var);
char            **ft_split(char *str, char *charset);
void            handle_env(char *cmd, char *arg);
void			print_env(void);
int		        envv_len(char **envv);
void    		remove_env_var(int var_pos);
void		    handle_export(char *str);
void		    handle_unset(char *str);
char            *malloc_sortie(int len);
int		        calc_c(char *str, char c);
char		    *parse_dollar(char *str);
char			*trim_quote(char *str, int *ret, int *xet);
int		        only_point(char *str);

#endif // !MINISHELL_H