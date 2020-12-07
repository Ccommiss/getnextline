#include "get_next_line.h"
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>

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

char *ft_fill_line(char *stock, int i, char *line)
{
	int j;
	int e;

	j = 0;
	e = 0;
	if(!(line = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	while (j < i)
		line[j++] = stock[e++];
	line[j] = '\0';
	return (line);
}

char *ft_strconcat(char *s1, char *s2, int size)
{
	char *concat;
	int i;
	int j;

	i = ft_strlen(s1);
	j = size;
	if (!(concat = (char *)malloc(sizeof(char) * (i + size + 1))))
		return NULL;
	if (s1)
		while (*s1)
			*concat++ = *s1++;
	if (*s2)
		while (size--)
			*concat++ = *s2++;
	*(concat) = '\0';
//	if (s1)
	//	free(s1); //on free le stock d'origine
	return (concat - i - j);
}

char	*ft_newstock(char **stock, int i)
{
	char *newstock;
	int j;

	j = 0;
	if(!(newstock = (char *)malloc(ft_strlen(*stock) - i + 1)))
		return (NULL);
//	printf ("STOCK J %c ; ", (*stock + i)[0]);
	while (((*stock + i)[j]) != '\0')
	{
		newstock[j] = (*stock + i)[j];
		j++;
	}
	newstock[j] = '\0';
	free(*stock); //on free l'ancien stock
	return (newstock);
}

int get_next_line(int fd, char **line)
{
	int size;
	char buf[4];
	static char *stock;
	int i;

	i = 0;
	while ((((size = read(fd, buf, 4)) > 0)) || stock[i])
	{
		if (size > 0)
			stock = ft_strconcat(stock, buf, size);
		while (stock[i])
		{
			//	printf("%d\n", i);
			if (stock[i] == '\n')
			{
				*line = ft_fill_line(stock, i, *line);
				stock = ft_newstock(&stock, i + 1);
				return (1);
			}
			i++;
		}
	}
	free(stock);
	return (0);
}

int main()
{
	char *line;
	line = NULL;

	int fd = open("poesie", O_RDONLY);
	printf("fd = %d\n", fd);
	while (get_next_line(fd, &line) == 1){
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	//while (1);
	return 0;
}
