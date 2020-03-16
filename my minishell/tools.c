
#include "minishell.h"

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;
	size_t	i;

	if (!n)
		return ;
	ptr = s;
	i = 0;
	while (i < n)
		*(ptr + i++) = 0;
}

void	*ft_memalloc(size_t size)
{
	void	*mem;

	if (!(mem = malloc(size)))
		return (NULL);
	ft_bzero(mem, size);
	return (mem);
}

int		envv_len(char **envv)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (envv[++i])
		count++;
	return (count);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = -1;
	while (++i < (int)strlen(s) + 1)
		if (*(s + i) == (char)c)
			return ((char *)s + i);
	return (NULL);
}

int		ft_strstartswith(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s2[++i])
		if (s1[i] != s2[i])
			return (0);
	return (1);
}

char	*ft_strjoinch(char const *s1, char c)
{
	char	*new_str;
	size_t	i;
	size_t	s1_len;

	if (!s1 || !c)
		return (NULL);
	s1_len = strlen(s1);
	new_str = ft_strnew(s1_len + 1);
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < s1_len)
		*(new_str + i) = *(s1 + i);
	*(new_str + i) = c;
	return (new_str);
}

char	**split_commande(char *line)
{
	int		i;
	char	**dest;

	if (!(dest = (char**)malloc(sizeof(char*) * 2)))
		return (NULL);
	if (!(dest[0] = malloc(sizeof(char) * 10)))
		return (NULL);
	if (!(dest[1] = malloc(sizeof(char) * (ft_strlenx(line) + 1))))
		return (NULL);
	i = -1;
	while (line[++i] != ' ' && line[i])
		dest[0][i] = line[i];
	dest[0][i] = '\0';
	line = line + i;
	i = -1;
	while (line[++i])
		dest[1][i] = line[i];
	dest[1][i] =  '\0';
	return (dest);
}