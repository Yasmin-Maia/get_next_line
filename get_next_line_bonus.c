/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasmin <yasmin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:24:47 by yasmin            #+#    #+#             */
/*   Updated: 2025/05/02 15:02:48 by yasmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	read_file(char *bag)
{
	int	i;

	i = 0;
	if (bag == NULL)
		return (0);
	while (bag[i] != '\0')
	{
		if (bag[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*remove_read_line(char *bag)
{
	int		i;
	int		j;
	char	*new_bag;

	i = 0;
	j = 0;
	if (!bag)
		return (NULL);
	while (bag[i] != '\n' && bag[i] != '\0')
		i++;
	if (bag[i] == '\0')
		return (free(bag), NULL);
	new_bag = ft_calloc(sizeof(char), (gnl_strlen(bag) - i + 1));
	if (!new_bag)
		return (free(bag), NULL);
	i++;
	while (bag[i] != '\0')
	{
		new_bag[j] = bag[i];
		i++;
		j++;
	}
	free(bag);
	return (new_bag);
}

static char	*get_line(int fd, char *bag)
{
	ssize_t	bytes_read;
	char	*buffer;
	char	*backup;

	buffer = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (read_file(bag) == 0 && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), free(bag), NULL);
		buffer[bytes_read] = '\0';
		backup = ft_strjoin(bag, buffer);
		if (!backup)
			return (free(buffer), free(bag), NULL);
		free(bag);
		bag = backup;
	}
	free(buffer);
	return (bag);
}

static char	*write_line(char *bag)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	if (!bag || bag[0] == '\0')
		return (NULL);
	while (bag[i] != '\n' && bag[i] != '\0')
		i++;
	line = (char *)ft_calloc(sizeof(char), (i + 2));
	if (!line)
		return (NULL);
	while (bag[j] != '\n' && bag[j] != '\0')
	{
		line[j] = bag[j];
		j++;
	}
	if (bag[j] == '\n')
		line[j++] = '\n';
	line[j] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*bag[FD_SIZE];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_SIZE)
		return (NULL);
	if (!bag[fd])
		bag[fd] = ft_calloc(sizeof(char), 1);
	bag[fd] = get_line(fd, bag[fd]);
	if (!bag[fd])
		return (NULL);
	line = write_line(bag[fd]);
	bag[fd] = remove_read_line(bag[fd]);
	if (!line)
		return (NULL);
	return (line);
}
