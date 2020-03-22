#include "minishell.h"

void			cd_simple(char *path)
{
	char	*cwd;
	int		i;
	char	buff[4097];

	cwd = getcwd(buff, 4096);
	i = 0;
	while (path[i] == ' ')
		i++;
	path = path + i;
	if (only_point(path) == 1 && ft_strlenx(path) > 2)
	{
		ft_putstr("cd: ");
		ft_putstr(path);
		ft_putstr(" not a directory \n");
	}
	else if (!chdir(path))
		set_env_var("OLDPWD", cwd);
	else
	{
		ft_putstr("cd: ");
		if (access(path, F_OK) == -1)
			ft_putstr("no such file or directory: ");
		else if (access(path, R_OK) == -1)
			ft_putstr("permission denied: ");
		else
			ft_putstr("not a directory: ");
		ft_putstr(path);
		ft_putstr("\n");
	}
}

void			cd_complex(void)
{
	char	*cwd;
	int		i;
	int		ret;
	int		xet;
	char	buff[4097];
	char	*dest;
	
	cwd = getcwd(buff, 4096);
	if (!(dest = malloc(sizeof(char) * (ft_strlenx(cwd) + 1))))
		exit_shell();
	ret = 0;
	i = 0;
	while(cwd[i])
	{
		if (cwd[i] == '\\')
			ret++;
		i++;
	}
	i = 0;
	xet = 0;
	while (cwd[i] && xet < ret)
	{
		if (cwd[i] == '\\')
			xet++;
		dest[i] = cwd[i];
		i++;
	}
	dest[i] = '\0';
	cd_simple(dest);
}

void	cd_handle_home(void)
{
	char	*cwd;
	char	*buff;
	char	*parsed_cwd;
	int		ret;
	int		i;

	if (!(buff = malloc(sizeof(char) * 4097)))
		return ;
	cwd = getcwd(buff, 4096);
	ret = 0;
	i = 0;
	while (cwd[i]  && ret < 3)
	{
		if (cwd[i] == '\\')
			ret++;
		i++;
	}
	cwd = ft_substr(cwd, 0, i);
	cd_simple(cwd);
}

void	handle_cdx(char *path)
{
	char	*str;
	char	**tab;

	while (*path == ' ')
		path++;
	tab = ft_split(path, " ");
	if ((strcmp(path, "\0") == 0 || strcmp(path, "~") == 0 || strcmp(path, "--") == 0))
		cd_handle_home();
	else if (strcmp(tab[1], "\0") != 0)
		ft_putstr("minishell : too many argument \n");
	else if (path[0] == '$')
		cd_simple(parse_dollar(path));
	else if (strcmp(path, "-") == 0)
	{
		str = g_envv[find_env_var("OLDPWD")];
		while (*str != '=')
			str++;
		if (strcmp(++str, " ") == 0)
			ft_putstr("minishell : OLDPWD not defined \n");
		else
			cd_simple(str);
	}
	else if (strcmp(tab[1], "..") == 0)
		cd_complex();
	else if (strcmp(tab[1], ".") == 0)
		;
	else
		cd_simple(path);
}

void	extendss(char *str, char c)
{
	int		i;
	char	*line;

	i = 0;
	while (str[ft_strlenx(str) - 1] != c && calc_c(str, c) % 2 != 0)
	{
		line = NULL;
		ft_putstr("quote > ");
		get_next_line(0, &line);
		str = ft_strjoin(str, "\\n");
		str = ft_strjoin(str, line);
	}
    ft_putstr("minishell : ");
    ft_putstr(str);
    ft_putstr(" not found \n");
}

void	handle_cd_x(char *dest, char *str)
{
	char	**tab;

	tab = split_commande(dest);
	if (((tab[1][0] == '"' || tab[1][0] == '\'') && (tab[1][1] == ' ' || tab[1][1] == '\0'))
		|| ((tab[1][ft_strlenx(tab[1])] == '"' || tab[1][ft_strlenx(tab[1])] == '\'') && (tab[1][ft_strlenx(tab[1]) - 1] == ' ' || tab[1][ft_strlenx(tab[1]) - 1] == '\0')))
	{
		ft_putstr("command error :");   
		ft_putstr(tab[0]);
	}
	else
	{
		while (*tab[1] == ' ')
			*tab[1]++;
		tab[1] = tab[1][0] == '"' || tab[1][0] == '\'' ?
		ft_substr(tab[1], 1, ft_strlenx(tab[1]) - 2) : ft_substr(tab[1], 0, ft_strlenx(tab[1]));
		tab[1] = ft_strjoin(" ", tab[1]);
		str = ft_strjoin(tab[0], tab[1]);
		handle_cdx(str);
	}
}

void	handle_cd(char *str)
{
    char	*dest;
    int		ret;
	int		xet;
	
	dest = trim_quote(str, &ret, &xet);
	if (ret % 2 != 0 && ret != 0)
		extendss(dest, '\"');
	else if (xet % 2 != 0 && xet != 0)
		extendss(dest, '\'');
	else
		handle_cd_x(dest, str); 
}