/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_pol2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 18:14:31 by polmarti          #+#    #+#             */
/*   Updated: 2024/01/28 20:31:13 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

int ft_strlen(char *str)
{
	if (!str)
		return (0);
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

char *ft_strchr(char *str, char c)
{
	int i = 0;
	while(str[i] != c && str[i])
		i++;
	if (str[i] == c)
		return (&str[i]);
	return (NULL);
}

char *ft_strjoin(char *s1, char *s2)
{
	int i = 0;
	int i2 = 0;
	char *str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s2)
		return (NULL);
	if (s1)
	{
		while(s1[i])
		{
			str[i] = s1[i];
			i++;
		}
		free(s1);
	}
	while(s2[i2])
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
		return(NULL);
	if (str[start] == '\0') //esto no esta bien, es si start es mayor o igual que la longitud del string ❌
		return (NULL);
	if (len >= ft_strlen(str) - start)
		len = ft_strlen(str) - start;
	char *rtrn = malloc(sizeof(char) * (len + 1));
	int i = 0;
	while(len--)
	{
		rtrn[i] = str[start];
		i++;
		start++;
	}
	rtrn[i] = '\0';
	return (rtrn);
}

char *ft_read_join(int fd, char *store)
{
	int cntrl = 1;
	char *str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	str[0] = '\0';
	while(cntrl > 0 && !ft_strchr(str, '\n'))
	{
		cntrl = read(fd, str, BUFFER_SIZE);
		if (cntrl == -1)
			return (free(str), NULL);
		if (cntrl == 0)
			return (free(str), NULL); //esto no esta bien, debe parar el bucle solo
		str[cntrl] = '\0'; //esta linea va antes de la condicion de cntrl 0
		store = ft_strjoin(store, str);
	}
	free(str);
	return(store);
}

char *ft_fill_line(char *store)
{
	if (!store)
		return (NULL);
	char *tmp = ft_strchr(store, '\n');
	if (!tmp)
		tmp = ft_strchr(store, '\0');
	char *str = ft_substr(store, 0, (ft_strlen(store) - ft_strlen(tmp) + 1));
	if (!str)
		return (NULL);
	return (str);
}

char *ft_clean_store(char *store)
{
	char *tmp = ft_strchr(store, '\n');
	if (!tmp)
		return (free(store), NULL);
	char *str = ft_substr(store, (ft_strlen(store) - ft_strlen(tmp)) + 1, ft_strlen(store)); //el limite debe ser tamano total - punto de inicio
	free(store);
	return (str);
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
		if (!store)
			return (NULL);
	}
	line = ft_fill_line(store);
	if (!line)
		return (NULL);
	store = ft_clean_store(store);
	return (line);
}

/*int main(void)
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
}*/
