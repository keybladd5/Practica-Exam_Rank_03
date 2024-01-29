/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_pol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:52:36 by polmarti          #+#    #+#             */
/*   Updated: 2024/01/28 20:44:16 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#define BUFFER_SIZE 10

int ft_strlen(char *str )
{
	if (!str)
		return (0);
	int i = 0;
	while(str[i])
		i++;
	return (i);
}

char *ft_strchr(char *str, char c)
{
	int i = 0;
	while (str[i] != c && str[i])
		i++;
	if (str[i] == c)
		return(&str[i]);
	return (NULL);
}

char *ft_strjoin(char *s1, char *s2)
{
	if(!s2)
		return (NULL);
	int i = 0;
	char *str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	int i2 = 0;
	if(s1)
	{
		while(s1[i])
		{
			str[i] = s1[i];
			i++;
		}
		free(s1);
	}
	while (s2[i2])
	{
		str[i] = s2[i2];
		i++;
		i2++;
	}
	str[i] = '\0';
	return (str);
}

char *ft_substr(char *str, int start, int len)
{
	if (!str)
		return (NULL);
	if (!str[start])
		return (NULL);
	if (len >= (ft_strlen(str) - start))
		len = ft_strlen(str) - start;
	int i = 0;
	char *rtrn = malloc(sizeof(char) * (len + 1));
	while(len--)
	{
		rtrn[i] = str[start];
		i++;
		start++;
	}
	rtrn[i] = '\0';
	return (rtrn);
}
//lee por tanto READ, puede que no lea, asi que devuelve NULL
char *ft_read_join(int fd, char *store)
{
	int cntrl = 1;
	char *buff = malloc(sizeof(char) * (BUFFER_SIZE + 1) );
	buff[0] = '\0';
	while (cntrl > 0 && !ft_strchr(buff, '\n'))
	{
		cntrl = read(fd, buff, BUFFER_SIZE);
		buff[cntrl] = '\0';
		if (cntrl > 0)
			store = ft_strjoin(store, buff);
	}
	free(buff);
	return (store);
}

char *ft_fill_line(char *store)
{
	if (!store)
		return (NULL);
	char *str = NULL;
	if (!ft_strchr(store, '\n'))
	{
		str = ft_strchr(store, '\0');
	}
	else
		str = ft_strchr(store, '\n');
	str = ft_substr(store, 0, (ft_strlen(store) - ft_strlen(str) + 1));
	return(str);
}

char *ft_clean_store(char *store)
{
	char *tmp = NULL;
	char *rtrn = NULL;
	tmp = ft_strchr(store, '\n'); //me coloco en el ultimo punto de \n
	if (!tmp)
		return (free(store), NULL);
	rtrn  = ft_substr(tmp, 1, ft_strlen(store));
	free(store);
	return (rtrn);
}

char *get_next_line(int fd)
{
	static char *store = NULL;
	char *line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if ((store && !ft_strchr(store, '\n')) || !store)
	{
		store = ft_read_join(fd, store);
		if(!store)
			return (NULL);
	}
	line = ft_fill_line(store);
	if(!line)
		return (NULL);
	store = ft_clean_store(store);
	return (line);
}

#include <stdio.h>
int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *str = get_next_line(fd);
	printf("%s", str);
	while(str)
	{	
		free(str);
		str = get_next_line(fd);
		printf("%s", str);
	}
	return (0);
}
