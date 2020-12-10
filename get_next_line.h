
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

size_t	ft_strlen(const char *s);
int		get_next_line(int fd, char **line);
char	*ft_fill_line(char *stock, int i, char *line);
char	*ft_strconcat(char *s1, char *s2, int size);
char	*ft_newstock(char **stock, int i);

#endif
