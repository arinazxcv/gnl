/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minell <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 15:38:58 by minell            #+#    #+#             */
/*   Updated: 2021/11/28 15:39:01 by minell           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_l(char *result_line)
{
	char	div;
	int		len;

	len = 0;
	if (ft_strchr(result_line, '\n'))
		div = '\n';
	else
		div = '\0';
	while (result_line[len] != div)
		len++;
	return (len + 1);
}

char	*ft_read(char *begin, int fd)
{
	char	buf[BUFFER_SIZE + 1];
	int		readed;

	readed = 1;
	if (!begin)
	{
		readed = read(fd, buf, BUFFER_SIZE);
		if (readed <= 0)
			return (NULL);
		buf[readed] = '\0';
		begin = ft_strdup(buf);
	}
	while (!(ft_strchr(begin, '\n')) && readed)
	{
		readed = read(fd, buf, BUFFER_SIZE);
		buf[readed] = '\0';
		begin = ft_strjoin(begin, buf, 0);
	}
	return (begin);
}

char	*get_next_line_bonus(int fd)
{
	static char	*begin[1024];
	char		*tmp;
	char		*str;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	begin[fd] = ft_read(begin[fd], fd);
	if (!begin[fd])
		return (NULL);
	tmp = NULL;
	str = NULL;
	if (ft_strchr(begin[fd], '\n'))
	{
		tmp = begin[fd];
		str = ft_substr(tmp, 0, ft_l(begin[fd]));
		begin[fd] = ft_substr(tmp, ft_l(begin[fd]), ft_strlen(begin[fd]) - ft_strlen(str));
		free(tmp);
		return (str);
	}
	if (begin[0][fd] != '\0')
		str = ft_substr(begin[fd], 0, ft_l(begin[fd]));
	free(begin[fd]);
	begin[fd] = NULL;
	return (str);
}

int main()
{
	int fd1= open("t1.txt", O_RDONLY);
	int fd2= open("t2.txt", O_RDONLY);
	int fd3= open("t3.txt", O_RDONLY);

	printf("%s", get_next_line_bonus(fd1));
	printf("%s", get_next_line_bonus(fd2));
	printf("%s", get_next_line_bonus(fd3));
	printf("%s", get_next_line_bonus(fd1));
	printf("%s", get_next_line_bonus(fd2));
	printf("%s", get_next_line_bonus(fd3));
	printf("%s", get_next_line_bonus(fd1));
	printf("%s", get_next_line_bonus(fd2));
	printf("%s", get_next_line_bonus(fd3));

}