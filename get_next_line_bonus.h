
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

char	*get_next_line_bonus(int fd);
char	*ft_strdup(const char *str);
int		ft_strlen(const char *a);
char	*ft_strchr(const char *str, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2, int f);
char	*ft_read_line(char *remainder, int fd);
int		len_of_line(char *result_line);

#endif
