#include "minishell.h"

char			*get_all_env(void)
{
	int		i;
	char		*buff;

	i = -1;
	buff = strdup(" ");
	while (g_envv[++i])
	{
		buff = ft_strjoin(buff, g_envv[i]);
		i++;
	}
	return (buff);
}

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
	char	*tmp;

	tmp = strdup(" ");
	while (*arg && *arg == ' ')
		*arg++;
	if (arg[0] == '>')
	{
		tmp = get_all_env();
		tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, arg);
		handle_redirect(tmp);
	}
	else if (strcmp(arg, "\0") != 0)
	{
		ft_putstr("env : << ");
		while (*arg && *arg != ' ')
		{
			write(1, arg, 1);
			++arg;
		}
		ft_putstr(" >> : no such file or directory \n");
	}
	else
		print_env();
}
