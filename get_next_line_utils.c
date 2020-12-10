#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_fill_line(char *stock, int i, char *line)
{
	int j;
	int e;

	j = 0;
	e = 0;
	if (!(line = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	while (j < i)
		line[j++] = stock[e++];
	line[j] = '\0';
	return (line);
}

char	*ft_strconcat(char *s1, char *s2, int size)
{
	char	*concat;
	char	*tmp;
	int		i;
	int		j;

	i = ft_strlen(s1);
	j = size;
	tmp = s1;
	if (!(concat = (char *)malloc(sizeof(char) * (i + size + 1))))
		return (NULL);
	if (s1)
		while (*s1)
			*concat++ = *s1++;
	if (s2)
		while (size--)
			*concat++ = *s2++;
	*(concat) = '\0';
	free(tmp);
	return (concat - i - j);
}

char	*ft_newstock(char **stock, int i)
{
	char	*newstock;
	int		j;

	j = 0;
	if (!(newstock = (char *)malloc(ft_strlen(*stock) - i + 1)))
		return (NULL);
	while (((*stock + i)[j]) != '\0')
	{
		newstock[j] = (*stock + i)[j];
		j++;
	}
	newstock[j] = '\0';
	free(*stock);
	if (newstock[0] != '\0')
		return (newstock);
	free(newstock);
	return (NULL);
}
