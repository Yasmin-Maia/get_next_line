/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasmin <yasmin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:24:47 by yasmin            #+#    #+#             */
/*   Updated: 2024/12/17 16:59:02 by yasmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
char *ft_remove_read_line(char *buffer)
{
	int		i;
	char	*new_buffer;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
	{
		new_buffer = ft_strdup(&buffer[i + 1]);
		free(buffer);
		return (new_buffer);
	}
	free(buffer);
	return (NULL);
}

char *ft_get_line(int fd, char *buffer)
{
    ssize_t bytes_read;
    char    *backup;
    char    *new_backup;

    backup = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (backup == NULL)
        return (NULL);
    bytes_read = 1;
    while (ft_read_file(buffer) == 0 && bytes_read != 0) 
    {
        bytes_read = read(fd, backup, BUFFER_SIZE);
        if (bytes_read == -1) 
            return (free(backup), free(buffer), NULL);
        backup[bytes_read] = '\0';
        new_backup = ft_strjoin(buffer, backup);
        if (!new_backup) 
            return (free(backup), free(buffer), NULL);
        free(buffer);
        buffer = new_backup;
    }
    free(backup);
    return (buffer);
}


char *get_next_line(int fd) 
{
    static char *buffer = NULL;
    char        *line;
    int         i;

    i = 0;
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (!buffer)
        buffer = ft_strdup("");
    buffer = ft_get_line(fd, buffer);
    if (!buffer)
        return (NULL);
    while (buffer[i] != '\n' && buffer[i] != '\0')
        i++;
    line = ft_substr(buffer, 0, i + (buffer[i] == '\n'));
    if (!line)
        return (NULL);
    buffer = ft_remove_read_line(buffer);
    return (line);
}


#include <stdio.h>

int main(void)
{
    int fd = open("test2.txt", O_RDONLY);
    if (fd == -1) 
	{
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL) 
	{
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}