#include "get_next_line.h"
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include <string.h>

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
	char *tmp;
	int i;
	int j;

	i = ft_strlen(s1);
	j = size;
	tmp = s1;
	if (!(concat = (char *)malloc(sizeof(char) * (i + size + 1))))
		return NULL;
	if (s1)
		while (*s1)
			*concat++ = *s1++;
	if (s2)
		while (size--)
			*concat++ = *s2++;
	*(concat) = '\0';
	if (tmp)
		free(tmp); //on free le stock d'origine
	return (concat - i - j);
}

char	*ft_newstock(char **stock, int i)
{
	char *newstock;
	int j;

	j = 0;
	if(!(newstock = (char *)malloc(ft_strlen(*stock) - i + 1)))
		return (NULL);
	while (((*stock + i)[j]) != '\0')
	{
		newstock[j] = (*stock + i)[j];
		j++;
	}
	newstock[j] = '\0';
	free(*stock); //on free l'ancien stock
	if (newstock[0] != '\0')
		return (newstock);
	else
	{
		free(newstock);
		return (NULL);
	}
}

int get_next_line(int fd, char **line)
{
	int size;
	char buf[BUFFER_SIZE];
	static char *stock = NULL;
	int i;

	i = 0;
	if (!fd || fd < 0 || line == NULL || BUFFER_SIZE <= 0 || read(fd, buf, 0) < 0)
		return (-1);
	while ((((size = read(fd, buf, BUFFER_SIZE)) > 0)) || (stock && stock[i]))
	{
		if (size > 0)
			stock = ft_strconcat(stock, buf, size);
		if (stock[i] == '\0')
			return (0);
		while (stock[i])
		{
			if (stock[i] == '\n')
			{
				*line = ft_fill_line(stock, i, *line);
				stock = ft_newstock(&stock, i + 1);
				return (1);
			}
			i++;
		}
	}
	*line = ft_fill_line(stock, i, *line);
	stock = NULL;
	free(stock);
	return (0);
}

// int main() {
//     int ret;
//     char *line;

//     line = 0;
//     ret = get_next_line(0, &line);

//     while (ret > 0) {
// 		write(1, "!", 1);
// 		// printf ("\nadd &line main = %p", &line);
// 		// printf ("\nadd line main = %p", line);


//         write(1, line, strlen(line));

//         write(1, "\n", 1);
//         free(line);
//         line = 0;
//         ret = get_next_line(0, &line);
//     }
//     if (ret == 0) {
// 		write(1, "???", 3);

//         write(1, line, strlen(line));

//         write(1, "\n", 1);
//         free(line);
//         line = 0;
//     }
// //	while (1);
// }

int main()
{
	int		fd;
	int		ret_value;
	char	*line;

	line = NULL;
	fd = open("line.txt", O_RDONLY);
	if (fd == -1)
		return (-1);
	while (get_next_line(fd, &line) == 1)
	{
		printf("%s\n", line);

	}
	printf("%s\n", line);
	free(line);
	close(fd);
	while (1);
	return (0);
}

// int		main()
// {
// 	int		fd;
// 	int		ret_value;
// 	char	*line;

// 	line = NULL;
// 	fd = open("poesie", O_RDONLY);
// 	if (fd == -1)
// 		return (-1);
// 	ret_value = 1;
// 	while (ret_value == 1)
// 	{
// 		ret_value = get_next_line(fd, &line);
// 		printf("%d |>>| %s\n", ret_value, line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }

// int main()
// {
//         int             fd;
//         int             i;
//         int             j;
//         char                    *line = 0;
//         char                    *lineadress[66];

//         j = 1;
//         printf("\n==========================================\n");
//         printf("========== TEST 1 : The Alphabet =========\n");
//         printf("==========================================\n\n");

//         if (!(fd = open("files/alphabet", O_RDONLY)))
//         {
//                 printf("\nError in open\n");
//                 return (0);
//         }
//         while ((i = get_next_line(fd, &line)) > 0)
//         {
//                 printf("|%s\n", line);
//                 lineadress[j - 1] = line;
//                 j++;
//         }
//         printf("|%s\n", line);
//         free(line);
//         close(fd);

//         if (i == -1)
//                 printf ("\nError in Fonction - Returned -1\n");
//         else if (j == 66)
//                 printf("\nRight number of lines\n");
//         else if (j != 66)
//                 printf("\nNot Good - Wrong Number Of Lines\n");
//       while (--j > 0)
//      	      free(lineadress[j - 1]);
//         j = 1;

//         printf("\n==========================================\n");
//         printf("========= TEST 2 : Empty Lines ===========\n");
//         printf("==========================================\n\n");

//         if (!(fd = open("files/empty_lines", O_RDONLY)))
//         {
//                 printf("\nError in open\n");
//                 return (0);
//         }
//         while ((i = get_next_line(fd, &line)) > 0)
//         {
//                 printf("|%s\n", line);
//                 free(line);
//                 j++;
//         }
//         printf("|%s\n", line); //ICI QUE CA BEUGUE
//         free(line);
//         close(fd);

//         if (i == -1)
//                 printf ("\nError in Fonction - Returned -1\n");
//         else if (j == 9)
//                 printf("\nRight number of lines\n");
//         else if (j != 9)
//                 printf("\nNot Good - Wrong Number Of Lines\n");
//         j = 1;
//         printf("\n==========================================\n");
//         printf("======== TEST 3 : The Empty File =========\n");
//         printf("==========================================\n\n");

//         if (!(fd = open("files/empty_file", O_RDONLY)))
//         {
//                 printf("\nError in open\n");
//                 return (0);
//         }
//         while ((i = get_next_line(fd, &line)) > 0)
//         {
//                 printf("|%s\n", line);
//                 free(line);
//                 j++;
//         }
//         printf("|%s\n", line);
//         free(line);
//         close(fd);

//         if (i == -1)
//                 printf ("\nError in Fonction - Returned -1\n");
//         else if (j == 1)
//                 printf("\nRight number of lines\n");
//         else if (j != 1)
//                 printf("\nNot Good - Wrong Number Of Lines\n");
//         j = 1;
//         printf("\n==========================================\n");
//         printf("========= TEST 4 : One New Line ==========\n");
//         printf("==========================================\n\n");

//         if (!(fd = open("files/1_newline", O_RDONLY)))
//         {
//                 printf("\nError in open\n");
//                 return (0);
//         }
//         while ((i = get_next_line(fd, &line)) > 0)
//         {
//                 printf("|%s\n", line);
//                 free(line);
//                 j++;
//         }
//         printf("|%s\n", line);
//         free(line);
//         close(fd);

//         if (i == -1)
//                 printf ("\nError in Fonction - Returned -1\n");
//         else if (j == 2)
//                 printf("\nRight number of lines\n");
//         else if (j != 2)
//                 printf("\nNot Good - Wrong Number Of Lines\n");
//         j = 1;
//         printf("\n==========================================\n");
//         printf("========= TEST 5 : Four New Lines ========\n");
//         printf("==========================================\n\n");

//         if (!(fd = open("files/4_newlines", O_RDONLY)))
//         {
//                 printf("\nError in open\n");
//                 return (0);
//         }
//         while ((i = get_next_line(fd, &line)) > 0)
//         {
//                 printf("|%s\n", line);
//                 free(line);
//                 j++;
//         }
//         printf("|%s\n", line);
//         free(line);
//         close(fd);

//         if (i == -1)
//                 printf ("\nError in Fonction - Returned -1\n");
//         else if (j == 5)
//                 printf("\nRight number of lines\n");
//         else if (j != 5)
//                 printf("\nNot Good - Wrong Number Of Lines\n");
//         j = 1;
//         printf("\n==========================================\n");
//         printf("============== TEST 6 : 42 ===============\n");
//         printf("==========================================\n\n");

//         if (!(fd = open("files/41_char", O_RDONLY)))
//         {
//                 printf("\nError in open\n");
//                 return (0);
//         }
//         while ((i = get_next_line(fd, &line)) > 0)
//         {
//                 printf("|%s\n", line);
//                 free(line);
//                 j++;
//         }
//         printf("|%s\n", line);
//         free(line);
//         close(fd);
//         if (!(fd = open("files/42_char", O_RDONLY)))
//         {
//                 printf("\nError in open\n");
//                 return (0);
//         }
//         while ((i = get_next_line(fd, &line)) > 0)
//         {

//                 printf("|%s\n", line);
//                 free(line);
//                 j++;
//         }
//         printf("|%s\n", line);
//         free(line);
//         close(fd);
//         if (!(fd = open("files/43_char", O_RDONLY)))
//         {
//                 printf("\nError in open\n");
//                 return (0);
//         }
//         while ((i = get_next_line(fd, &line)) > 0)
//         {
//                 printf("|%s\n", line);
//                 free(line);
//                 j++;
//         }
//         printf("|%s\n", line);
//         free(line);
//         close(fd);

//         if (i == -1)
//                 printf ("\nError in Fonction - Returned -1\n");
//         else if (j == 1)
//                 printf("\nRight number of lines\n");
//         else if (j != 1)
//                 printf("\nNot Good - Wrong Number Of Lines\n");
//         j = 1;
//         printf("\n==========================================\n");
//         printf("============= TEST 7 : Marge =============\n");
//         printf("==========================================\n\n");

//         int fd2;

//         if (!(fd = open("files/half_marge_top", O_RDONLY)))
//         {
//                 printf("\nError in open\n");
//                 return (0);
//         }
//         if (!(fd2 = open("files/half_marge_bottom", O_RDONLY)))
//         {
//                 printf("\nError in open\n");
//                 return (0);
//         }
//         while ((i = get_next_line(fd, &line)) > 0)
//         {
//                 printf("%s\n", line);
//                 free(line);
//                 j++;
//         }
//         free(line);
//         while ((i = get_next_line(fd2, &line)) > 0)
//         {
//                 printf("%s\n", line);
//                 free(line);
//                 j++;
//         }
//         printf("%s\n", line);
//         free(line);
//         close(fd);
//         close(fd2);

//         if (i == -1)
//                 printf ("\nError in Fonction - Returned -1\n");
//         else if (j == 25)
//                 printf("\nRight number of lines\n");
//         else if (j != 25)
//                 printf("\nNot Good - Wrong Number Of Lines\n");
//         j = 1;
//         printf("\n==========================================\n");
//         printf("========= TEST 8 : Wrong Input ===========\n");
//         printf("==========================================\n\n");

//         if (get_next_line(180, &line) == -1)
//                 printf("Well Done, you return -1 if no FD\n\n");
//         else
//                 printf("Not Good, you don't return -1 if no FD\n\n");
//         return (0);
// }
