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

	j = size;
	i = ft_strlen(s1);
	if (!(concat = (char *)malloc(sizeof(char) * (i + size + 1))))
		return NULL;
	if (s1)
		while (*s1)
			*concat++ = *s1++;
	if (*s2)
		while (size--)
			*concat++ = *s2++;
	*(concat) = '\0';
	free(s1); //on free le stock d'origine
	return (concat - i - j);
}

void	*ft_memcpy(void *dst, const void *src, size_t size)
{
	unsigned char *dst2;
	unsigned char *src2;

	if (!dst && !src)
		return (0);
	dst2 = (unsigned char *)dst;
	src2 = (unsigned char *)src;
	while (size-- > 0)
		*dst2++ = *src2++;

	//printf("add dst2 %p\n", &dst2);
	//printf("add src2 %p\n", &src2);
	return (dst);
}

// char *ft_empty_stock(char *stock, int i)
// {
// 	int j;
// 	char *tmp;

// 	j = 0;
// 	tmp = malloc(sizeof(char *) * (i));
// 	tmp = ft_memcpy(tmp, stock, i);
// //	printf("add tmp %p\n", tmp);
// //	printf("add stock %p\n", stock);
// //	printf ("tmp= %s\n", tmp);
// 	stock = stock + i + 1;
// 	free(tmp);
// 	return (stock);
// }

char	*ft_newstock(char *stock, int i)
{
	char *newstock;
	int j;

	j = 0;
	if(!(newstock = (char *)malloc(ft_strlen(stock) - i + 1)))
		return (NULL);
	while (stock[j])
	{
		newstock[j] = (stock + i)[j];
		j++;
	}
	newstock[j] = '\0';
	free(stock); //on free l'ancien stock
	return (newstock);
}

int get_next_line(int fd, char **line)
{
	int size;
	char buf[1];
	static char *stock;
	int i;

	i = 0;
	while ((((size = read(fd, buf, 1)) > 0)) || stock[i])
	{
		if (size > 0)
			stock = ft_strconcat(stock, buf, size);
		while (stock[i])
		{
			if (stock[i] == '\n')
			{
				*line = ft_fill_line(stock, i, *line);
				//stock = ft_newstock(stock, i);
				stock = ft_empty_stock(stock, i);
				return (1);
			}
			i++;
			free(line); //test
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
	while (1);
	//return 0;
}
