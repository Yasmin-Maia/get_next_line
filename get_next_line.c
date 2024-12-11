/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaia-do <ymaia-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:57:49 by ymaia-do          #+#    #+#             */
/*   Updated: 2024/12/11 18:35:44 by ymaia-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.c"

int ft_read_file(char *buffer)
{
	int	i;
	
	i = 0;
	if (buffer == NULL)
		return (0);
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char *ft_get_line(int fd, char *buffer)
{
	ssize_t	bytes_read;
	char	*backup;
	char	*new_backup;
	
	backup = malloc(sizeof(char) * (BUFFER_SIZE + 1))
	if (backup == NULL)
		return(NULL);
	bytes_read = 1;
	while (ft_read_file(backup) == 0 && bytes_read > 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))
		if (buffer == NULL)
			return(NULL);
		bytes_read = read(fd, backup, BUFFER_SIZE)
		if (bytes_read == -1)
			return (free(backup), free(buffer), NULL);
		new_backup = ft_strjoin(buffer, backup);
		buffer = new_backup;
	}
	return (buffer);
}

char *ft_remove_read_line(char *buffer)
{
	
}

char *get_next_line(int fd)
{
	static char	*buffer;
	
	
}
