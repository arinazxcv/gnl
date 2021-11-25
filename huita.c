#include "get_next_line.h"

int ft_strlen(const char *a) //utils
{
	size_t i;

	i = 0;
	while (a && a[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *str) // utils
{
	char	*arr;
	size_t	i;
	size_t	buf;

	i = 0;
	buf = ft_strlen(str);
	arr = (char *)malloc(sizeof(char) * (buf + 1));
	if (!arr)
		return (NULL);
	else
	{
		while (str[i])
		{
			arr[i] = (char)str[i];
			i++;
		}
	}
	arr[i] = '\0';
	return (arr);
}

char	*ft_strchr(const char *str, int c) //utils
{
	char	*temp;
	
	temp = (char*) str;
	while (*temp )
	{
		if (*temp == (char)c)
			return (temp);
		temp++;
	}
	if ((char)c == *temp)
		return (temp);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2, int f) // utils
{
	char	*arr;
	size_t	i;
	size_t	j;
	size_t	buf;

	i = 0;
	j = 0;
	buf = ft_strlen(s1) + ft_strlen(s2);
	arr = (char *)malloc(sizeof(char) * (buf + 1));
	if (!arr)
		return (NULL);
	else
	{
		while (s1 && s1[i])
			arr[j++] = s1[i++];
		i = 0;
		while (s2 && s2[i])
			arr[j++] = s2[i++];
		arr[j] = '\0';
	}
	if (f == 0 || f == 2)
		free((void*)s1);
	if (f == 1 || f == 2)
		free((void*)s2);
	return (arr);
}

char  *ft_catbuf(char *buf)
{
	char *temp;
	char *clon;

	clon = ft_strchr(buf, '\n');
	if (clon)
		clon[0] = '\0';
	temp = ft_strdup(buf);
	return (temp);
}

char *ft_begin(char *buf, char **begin_next_str)
{
	char *clon;
	char *temp;
	char *end_str;

	clon = ft_strdup("");
	if (buf)
	{
		buf = ft_strchr(buf, '\n');
		if (!buf)
			return (0);
		*buf = '\0';
		(*begin_next_str) = ft_strdup(++buf);
		// end_str = ft_catbuf(buf);
		// clon = ft_strjoin(clon, end_str, 2);
		// clon = ft_strjoin(clon, "\n", 0);
	}
	//char *begin_next_str
	else if (*begin_next_str)
	{
		temp = (*begin_next_str);
		(*begin_next_str) = ft_strchr(*begin_next_str, '\n');
		(**begin_next_str)='\0';
		(*begin_next_str)++;
		clon = ft_strdup(temp);
		// printf("RESULT: |%s|\n", clon);
	}
	return(clon);
}



char *ft_read(int fd, char *buf, char *str)
{
	char *end_str;
	static char *begin_nex;
	int len_str;
	char *clon;
	
	len_str = 0;
	str = ft_strdup("");
	if (ft_strlen(begin_nex) > 0)
		str = ft_strjoin(str, begin_nex, 0);
	buf[len_str] = '\0';
	int ind = 1;
	// while (read(fd, buf, BUFFER_SIZE))
	int count = 4;
	while (read(fd, buf, BUFFER_SIZE) || count--)
	{
		// printf("LEN: %d %s\n", ind, begin_nex);
		if(ft_strchr(buf, '\n'))
		{
			str = ft_begin(buf, &begin_nex); // leak
			end_str = ft_catbuf(buf);
			
			str = ft_strjoin(str, end_str, 2);
			str = ft_strjoin(str, "\n", 0);
			// printf("|%s|\n", begin_nex);
			return(str);
		}

		str = ft_strjoin(str, buf, 0);
		
	}
	free(str);
	return(str);
}


char *get_next_line(int fd)
{
	char *str;
	char buf[BUFFER_SIZE + 1];
	
	str = NULL;
	str = ft_read(fd, buf, str);
	return (str);
}

int main()
{
	int f;
	int i;

	i = 10;

	f = open("text.txt", O_RDONLY);
//	while (i--)
	//printf("%s",get_next_line(f));
	//while(i--)
		printf("%s", get_next_line(f));
		printf("%s", get_next_line(f));

}
