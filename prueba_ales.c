/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-tole <ade-tole@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:53:07 by ade-tole          #+#    #+#             */
/*   Updated: 2024/01/27 19:01:06 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

char	*ft_strchr(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	if (*str == c)
		return (str);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (s1 && s1[len])
		len++;
	while (s2 && s2[i])
	{
		len++;
		i++;
	}
	str = malloc(len + 1);
	len = 0;
	if (s1)
	{
		while (s1[len])
		{
			str[len] = s1[len];
			len++;
		}
		free (s1);
	}
	i = 0;
	while (s2 && s2[i])
	{
		str[len] = s2[i];
		len++;
		i++;
	}
	str[len] = '\0';
	return (str);
}

char	*ft_substr(char *str, int len)
{
	char	*substr;
	int		i = 0;

	substr = malloc(len + 1);
	while (len--)
	{
		substr[i] = *str;
		i++;
		str++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_clean_storage(char *storage)
{
	char	*clean_storage;

	clean_storage = ft_substr(ft_strchr(storage, '\n') + 1, \
			(int)(ft_strchr(storage, '\0') - ft_strchr(storage, '\n') - 1));
	free (storage);
	return (clean_storage);
}

char	*ft_empty_storage(char *storage)
{
	char	*last_line;
	int		i = 0;

	while (storage[i])
		i++;
	last_line = malloc(i + 1);
	i = 0;
	while (storage[i])
	{
		last_line[i] = storage[i];
		i++;
	}
	last_line[i] = '\0';
	storage = NULL;
	free (storage);
	return (last_line);
}


char	*get_next_line(int fd)
{
	static char	*storage = NULL;
	char		*line = NULL;//modificado pol
	char		*buff = NULL; //modificado pol
	int			rdbytes = 1;

	buff = malloc(BUFFER_SIZE + 1);
	while (rdbytes > 0 && !ft_strchr(buff, '\n'))
	{
		rdbytes = read(fd, buff, BUFFER_SIZE);
		buff[rdbytes] = '\0';
		if (rdbytes > 0)
			storage = ft_strjoin(storage, buff);
	}
	free (buff);
	if (!ft_strchr(storage, '\n'))
		return (ft_empty_storage(storage));
	line = ft_substr(storage, (int)(ft_strchr(storage, '\n') - storage + 1));
	storage = ft_clean_storage(storage);

	return (line);
}

#include <stdio.h>
#include <fcntl.h>

int main()
{
	int	fd = open("test.txt", O_RDONLY);
	//int i = 5;
	char *str = get_next_line(fd);
	printf("%s", str);
	while(str)
	{
		free(str);
		str = get_next_line(fd);
		printf("%s", str);	
	}
	return 0;
}
