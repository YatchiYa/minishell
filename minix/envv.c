#include "minishell.h"

void			print_env(void)
{
	int		i;

	i = -1;
	while (g_envv[++i])
	{
		ft_putstr(g_envv[i]);
		ft_putstr("\n");
	}
}

int				envv_len(char **envv)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (envv[++i])
		count++;
	return (count);
}

void			remove_env_var(int var_pos)
{
	int		i;
	int		var_count;

	free(g_envv[var_pos]);
	g_envv[var_pos] = NULL;
	i = var_pos;
	var_count = var_pos + 1;
	while (g_envv[i + 1])
	{
		g_envv[i] = strdup(g_envv[i + 1]);
		free(g_envv[i + 1]);
		i++;
		var_count++;
	}
	g_envv = realloc_envv(var_count - 1);
}

void			handle_env(char *cmd, char *arg)
{
	if (strcmp(arg, "\0") != 0)
		ft_putstr("env : no such file or directory \n");
	else
		print_env();
}