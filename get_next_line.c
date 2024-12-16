/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaia-do <ymaia-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:57:49 by ymaia-do          #+#    #+#             */
/*   Updated: 2024/12/16 17:06:58 by ymaia-do         ###   ########.fr       */
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
	return (buffer);
}

char *ft_get_line(int fd, char *buffer)
{
	ssize_t	bytes_read;
	char	*backup;
	char	*new_backup;
	
	backup = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (backup == NULL)
		return(NULL);
	bytes_read = 1;
	while (ft_read_file(backup) == 0 && bytes_read != 0)
	{
		bytes_read = read(fd, backup, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(backup), free(buffer), NULL);
		new_backup = ft_strjoin(buffer, backup);
		if (!new_backup)
			return (free(backup), NULL);
		free(buffer);
		buffer = new_backup;
	}
	if (ft_read_file(backup) == 1)
		buffer = ft_remove_read_line(buffer);
	return (free(backup), buffer);
}


char *get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	
}

int main(void)
{
    int fd = open("arquivo.txt", O_RDONLY);
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