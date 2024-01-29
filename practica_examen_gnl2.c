/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practica_examen_gnl2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 12:11:17 by polmarti          #+#    #+#             */
/*   Updated: 2024/01/28 20:32:33 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	if (!str)
		return (0);
	int i = 0;
	while(str[i])
		i++;
	return(i);
}
//mejor iterar con integers
char	*ft_strchr(char *str, char c)
{
	int i = 0;
	while (str[i] != c && str[i])
	{
		if (str[i] == c)
			return (str[i]);
		i++;
	}
	if (str[i] == c)
		return (str[i]);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int i = 0;
	int i2 = 0;
	char *str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)+ 1))
	if (!s2)
		return (NULL);
	if(s1)//es asi o *s1? 
	{
		while(s1[i])
		{
			str[i] = s1[i];
			i++;
		}
		free(s1);//es correcto liberar aqui?puede dar error si existe pero no esta alojado?
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
char	*ft_substr(char *str, int start, int len)
{
	if (!str)
		return (NULL);
	if (start >= ft_strlen(str))
		return (NULL);
	if (len >= (ft_strlen(str) - start)) // si la longitud total a copiar supera el tamano restante de modificar el punto de inicio de la cadena
		len = ft_strlen - start; //el tamano de len se ajusta al total posible de modificar el inicio de la cadena
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
	int i = 0;
	int cntrl = 1;
	char *buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (cntrl > 0 && !ft_strchr(store, '\n'))
	{
		cntrl = read()
	}

}
char *get_next_line(int fd)
{
	static char *store = NULL;
	char *line = NULL;
	if (fd < 0 || ) //no recuerdo esta condicion
	if (store && !ft_strchr(store) || !store) //si hay store pero no \n o store es NULL
	{
		store = ft_read_join(fd);
		if (!store) //en caso de ultima lectura fallara y no habra store, por eso devolver null para evitar el segfault
			return (NULL);
	}
	line = ft_fill_line(store);
	store = ft_clean_store;
	return (line);
}

