/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isitbon <isitbon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:18:28 by isitbon           #+#    #+#             */
/*   Updated: 2023/05/22 17:46:42 by isitbon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_line(char *buffer, char *b)
{
	char	*t;

	t = ft_strjoin(buffer, b);
	free(buffer);
	return (t);
}

char	*get_new_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (buffer == NULL)
		return (0);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*read_line(int fd, char *str)
{
	char	*buffer;
	int		br;

	br = 1;
	if (!str)
		str = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (free(str), NULL);
	while (br > 0)
	{
		br = read(fd, buffer, BUFFER_SIZE);
		if (br < 0)
			return (free(buffer), NULL);
		buffer[br] = 0;
		str = free_line(str, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (str);
}

char	*further_line(char *buffer)
{
	int		i;
	int		i2;
	char	*line;

	i = 0;
	i2 = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] && buffer[i] == '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	while (buffer[i])
		line[i2++] = buffer[i++];
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = read_line(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_new_line(buffer);
	buffer = further_line (buffer);
	if (!line || line[0] == 0)
	{
		free(line);
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	return (line);
}
