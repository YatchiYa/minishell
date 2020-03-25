#include "minishell.h"

char    *malloc_sortie(int len)
{
    char    *str;

    if (!(str = malloc(sizeof(char) * (len + 1))))
        return (NULL);
    return (str);
}

int		calc_c(char *str, char c)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == c)
			ret++;
		i++;
	}
	return (ret);
}

void	extend(char *str, char c)
{
	int		i;
	char	*line;
	int		back;

	i = 0;
	back = 0;
	while (str[ft_strlenx(str) - 1] != c && calc_c(str, c) % 2 != 0)
	{
		line = NULL;
		ft_putstr("quote > ");
		get_next_line(0, &line);
		str = ft_strjoin(str, "\n");
		str = ft_strjoin(str, line);
	}
	while (str[i])
	{
		i = 0;
		while (str[i] == ' ')
			i++;
		if (str[i] == '-' && str[i + 1] == 'n')
		{
			back = 1;
			i += 2;
		}
		while (str[i])
		{
			if (str[i] != '\'' && str[i] != '\"')
			{
				if (str[i] == '$')
				{
					ft_putstr(parse_dollar(&str[i]));
					while (str[i] != ' ' && str[i] && str[i] != '\0')
						i++;
					i--;
				}
				else
					write(1, &str[i], 1);
			}
			i++;
		}
		if (back == 1)
			;
		else
    		ft_putstr("\n");   
	}       
    ft_putstr("\n");   
}

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

void    handle_echo(char *str)
{
    	int		i;
    	char	*dest;
    	int		ret;
	int		xet;
	int		back;

    	i = -1;
    	dest = malloc_sortie(ft_strlenx(str));
    	while (str[++i])
        	dest[i] = str[i];
    	dest[i] = '\0';
    	i = -1;
	ret = 0;
	xet = 0;
	back = 0;
    	while (dest[++i])
	{
		if (dest[i] == '"' && xet == 0)
			ret++;
		else if (dest[i] == '\'' && ret == 0)
			xet++;
	}
	if (ret % 2 != 0 && ret != 0)
		extend(dest, '\"');
	else if (xet % 2 != 0 && xet != 0)
		extend(dest, '\'');
	else if ((ssx(dest, ">|<") == 1) && (search_delim(dest, '"', ret) == 1))
		handle_redirect(dest);
	else
	{
		i = 0;
		while (str[i] == ' ')
			i++;
		if (str[i] == '-' && str[i + 1] == 'n')
		{
			back = 1;
			i += 2;
		}
		while (str[i])
		{
			if (str[i] != '\'' && str[i] != '\"')
			{
				if (str[i] == '$')
				{
					ft_putstr(parse_dollar(&str[i]));
					while (str[i] != ' ' && str[i] && str[i] != '\0')
						i++;
					i--;
				}
				else
					write(1, &str[i], 1);
			}
			i++;
		}
		if (back == 1)
			;
		else
    		ft_putstr("\n");   
	}
}
