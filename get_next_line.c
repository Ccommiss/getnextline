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
	while (s[i] != '\0')
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

char *ft_strconcat(char *s1, char *s2)
{
	char *concat;
	int i;
	int j;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (!(concat = (char *)malloc(sizeof(char) * (i + j + 1))))
		return NULL;
	if (s1)
		while (*s1)
			*concat++ = *s1++;
	while (*s2)
			*concat++ = *s2++;
	*concat = '\0';
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
	return (dst);
}

char *ft_empty_stock(char **stock, int i)
{
	int j;
//	char *tmp;

	j = 0;
//	tmp = malloc(sizeof(char *) * (i));
//	tmp = ft_memcpy(tmp, *stock, i);
	*stock = *stock + i + 1;
//	free(tmp);
	return (*stock);
}

int get_next_line(int fd, char **line)
{
	int size;
	char buf[78];
	static char *stock;
	int i;

	i = 0;
	while (((size = read(fd, buf, 78) > 0)) || stock[i])
	{
		if (size > 0)
			stock = ft_strconcat(stock, buf);
		while (stock[i])
		{
			if (stock[i] == '\n')
			{
				*line = ft_fill_line(stock, i, *line);
				ft_empty_stock(&stock, i);
				return (1);
			}
			i++;
		}
	}
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
		line = NULL;
	}
	return 0;
}
