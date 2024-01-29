/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_aux_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:48:09 by polmarti          #+#    #+#             */
/*   Updated: 2024/01/28 20:03:36 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

//#define BUFFER_SIZE 1

int	ft_strlen(char *str)
{
	if (!str)
		return (0);
	int i = 0;
	while (str[i])
		i++;
	return (i);
}
void ft_putstr(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}
char *ft_strchr(const char *str, char c)
{
	while(*(char *)str && *(char *)str != c)
		str++;
	if (*(char *)str != c)
		return (NULL);
	return ((char *)str);
}
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr = NULL; 

	ptr = (unsigned char *)dest;
	if (!dest && !src)
		return (dest);
	while(n-- > 0)
	{
		*ptr++ = *(unsigned char *)src;
		src++;
	}
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char *rtrn = NULL;
	int i = 0;
	int i2 = 0;
	if (!s2)
		return (NULL);
	rtrn = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)+1));
	if (s1)
	{
		while(s1[i])
		{
			rtrn[i] = s1[i];
			i++;
		}
		free(s1);
	}
	while(s2[i2])
	{
		rtrn[i] = s2[i2];
		i++;
		i2++;
	}
	rtrn[i] = '\0';
	return (rtrn);
}

char	*ft_substr(char *str, unsigned int start, unsigned int len)
{
	char *rtrn = NULL;
	int i = 0;
	if (!str)
		return (NULL);
	if ((int)len > (ft_strlen(str) - (int)start))
		len = ft_strlen(str) - (int)start;
	if ((int)start >= ft_strlen(str))
	{
		rtrn = (char *)malloc(sizeof(char)*1);
		rtrn[0] = '\0';
		return (rtrn);
	}
	rtrn = (char *)malloc(sizeof(char)* (len + 1));
	while(len--)
	{
		rtrn[i] = str[start];
		i++;
		start++;
	}
	rtrn[i] = '\0';
	return (rtrn);
}
//read and join on the static
char *ft_read_join(int fd, char *store)
{
	int read_char = 1;
	char *str = malloc(sizeof(char) * (BUFFER_SIZE +1));
	str[0] = '\0';
	while (read_char > 0 && !ft_strchr(str, '\n'))
	{
		read_char = read(fd, str, BUFFER_SIZE);
		if (read_char == -1)
			return (NULL);
		str[read_char] = '\0';
		if (read_char == 0)
			break ;
		store = ft_strjoin(store, str);
	}
	free(str);
	return (store);
}
//fecth the line to return 
char *ft_fill_line(char *store)
{
	char *tmp;
	char *str;

	if (store[0] == '\0')
		return (NULL);
	tmp = ft_strchr(store, '\n');
	if (!tmp)
		tmp = ft_strchr(store, '\0');
	str = ft_substr(store, 0, ((tmp - store) + 1));
	//str = ft_substr(str, 0, ft_strlen(tmp))); Tambien deberia valer no? 
	return (str);
}
//clear the line fetched from static
char *ft_clean_store(char *store)
{
	int start;
	char *tmp;
	char *str;

	tmp = ft_strchr(store, '\n');
	if (!tmp)
		return (free(store), NULL);
	start = (tmp - store) + 1;
	if (!store[start])
		return (free(store), NULL);
	str = ft_substr(store, start, (ft_strlen(store) - start));
	free(store);
	return (str);
}


//read, fill and clean
char *get_next_line(int fd)
{
	static char *store = NULL;
	char *line = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if ((store && !ft_strchr(store, '\n')) || !store)//si tengo que leer
	{
		store = ft_read_join(fd, store);
		if (!store)
			return (NULL);
	}
	line = ft_fill_line(store);//relleno el string que voy a devolver
	if (!line)
		return (NULL);
	store = ft_clean_store(store);//quito el string que voy a devolver de la static
	return (line);
}

/*int main (int argc, char *argv[])
{
	if (argc > 2)
		return (1);
	int fd = open(argv[1], O_RDONLY); 
	char *str = get_next_line(fd);
	printf("%s", str);
	while(str)
	{	
		free(str);
		str = get_next_line(fd);
		printf("%s", str);
	}
	close(fd);
	return (0);	
}*/
