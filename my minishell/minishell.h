
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
# include "gnl/get_next_line.h"

# define IS_QUOTE(x) (x == '"' || x == '\'')

char	        **g_envv;


void	        *ft_memalloc(size_t size);
int             envv_len(char **envv);
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

#endif // !MINISHELL_H