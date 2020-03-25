#include "minishell.h"


int	ss(char c, char *delim)
{
	int	i;
	
	i = 0;
	while (delim[i])
	{
		if (delim[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ssx(char *str, char *delim)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (str[j])
	{
		i = 0;
		while (delim[i])
		{
			if (delim[i] == str[j])
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

int	search_delim(char *str, char c, int n)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i] && ss(str[i], ">|<") == 0)
	{
		if (str[i] == c)
			res++;
		i++;
	}
	if (res != n)
		return (0);
	return (1);
}

char	*delim_ptr(char *str)
{
	int	i;
	int	j;

	i = ft_strlenx(str) - 1;
	while (str[i] && ss(str[i], ">|<") == 0)
		i--;
	j = 0;
	while (str[j] && j < i)
		j++;
	return (&str[j]);
}

void	handle_1(char *str, char c)
{
	int	i;
	char	**tab;
	int	fd;

	tab = ft_strsplit(str, c);
	i = 0;
	while (tab[1] && *tab[1] == ' ')
		*tab[1]++;
	while (tab[0] && *tab[0] == ' ')
		*tab[0]++;
	fd = open(tab[1], O_RDWR | O_CREAT, S_IRWXU | O_TRUNC);
	while (tab[0][i])
	{
		if (tab[0][i] != '"' && tab[0][i] != '\'')
			write(fd, &tab[0][i], 1);
		i++;
	}
	write(fd, "\n", 1);
	close(fd);
}

void	handle_2(char *str, char c)
{
	int	i;
	char	**tab;
	int	fd;
	char	*line;
	int	ret;

	tab = ft_strsplit(str, c);
	i = 0;
	while (tab[1] && *tab[1] == ' ')
		*tab[1]++;
	while (tab[0] && *tab[0] == ' ')
		*tab[0]++;
	fd = open(tab[1], O_RDWR | O_CREAT, S_IRWXU | O_TRUNC);
	while ((ret = get_next_line(fd, &line)) > 0)
		ft_strjoin(tab[0], line);
	while (tab[0][i])
	{
		if (tab[0][i] != '"' && tab[0][i] != '\'')
			write(fd, &tab[0][i], 1);
		i++;
	}
	write(fd, "\n", 1);
	close(fd);
}


void	handle_redirect(char *str)
{
	int		i;
	char		*res;

	res = delim_ptr(str);
	if (res[0] == '>' && res[1] == '>')
		handle_2(str, '>');
	else if (res[0] == '>')
		handle_1(str, '>');
}
