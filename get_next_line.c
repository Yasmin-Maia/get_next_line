/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_next_line.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ymaia-do <ymaia-do@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/12/06 15:24:47 by yasmin			#+#	#+#			 */
/*   Updated: 2024/12/18 14:06:26 by ymaia-do		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_read_file(char *bag)
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

static char	*ft_remove_read_line(char *bag)
{
	int		i;
	char	*new_bag;

	i = 0;
	while (bag[i] != '\n' && bag[i] != '\0')
		i++;
	if (bag[i] == '\n')
	{
		new_bag = ft_strdup(&bag[i + 1]);
		free(bag);
		return (new_bag);
	}
	free(bag);
	return (NULL);
}

static char	*ft_get_line(int fd, char *bag)
{
	ssize_t	bytes_read;
	char	*buffer;
	char	*backup;

	buffer = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	bytes_read = 1;
	while (ft_read_file(bag) == 0 && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (free(buffer), free(bag), NULL);
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
	while (bag[i] != '\n' && bag[i] != '\0')
		i++;
	if (bag[i] == '\n')
		line = ft_calloc(sizeof(char), (i + 2));
	else
		line = ft_calloc(sizeof(char), (i + 1));
	while (bag[j] != '\n' && bag[j] != '\0')
	{
		line[j] = bag[j];
	}
	if (bag[j] == '\n')
	{
		line[j] = '\n';
		j++;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*bag;
	char		*line;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!bag)
		bag = ft_strdup("");
	bag = ft_get_line(fd, bag);
	if (!bag)
		return (NULL);
	line = write_line(bag);
	if (!line)
		return (NULL);
	bag = ft_remove_read_line(bag);
	return (line);
}

#include <stdio.h>

int main(void)
{
	int fd = open("test1.txt", O_RDONLY);
	
	char *line;
	while ((line = get_next_line(fd)) != NULL) 
	{
		printf("%s", line);
		free(line);
	}

	close(fd);
	return (0);
}