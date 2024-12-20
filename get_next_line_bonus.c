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

static char	*get_line(int fd, char *bag)
{
	ssize_t	bytes_read;
	char	*buffer;
	char	*backup;

	if (bag == NULL)
		bag = ft_calloc(sizeof(char), 1);
	bytes_read = 1;
	while (read_file(bag) == 0 && bytes_read != 0)
	{
		buffer = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
		if (!buffer)
			return (NULL);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1 || (bytes_read == 0 && bag[0] == '\0'))
			return (free(buffer), free(bag), NULL);
		if (bytes_read == 0)
			break ;
		backup = ft_strjoin(bag, buffer);
		free(buffer);
		if (!backup)
			return (free(bag), NULL);
		free(bag);
		bag = backup;
	}
	return (bag);
}

static char	*write_line(char *bag)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	if (!bag)
		return (NULL);
	while (bag[i] != '\n' && bag[i] != '\0')
		i++;
	line = ft_calloc(sizeof(char), (i + 2));
	if (!line)
		return (NULL);
	while (bag[j] != '\n' && bag[j] != '\0')
	{
		line[j] = bag[j];
		j++;
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
	static char	*bag[FD_SIZE];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_SIZE)
		return (NULL);
	if (!bag[fd])
		bag[fd] = ft_strdup("");
	bag[fd] = get_line(fd, bag[fd]);
	if (!bag[fd])
		return (NULL);
	line = write_line(bag[fd]);
	if (!line)
		return (NULL);
	bag[fd] = remove_read_line(bag[fd]);
	return (line);
}
/* 
int main(void)
{
	char	*s[] = {"test1.txt", "test2.txt", "test3.txt", 
	"test4.txt", "test5.txt", "test6.txt"};
	int		i = 0;
	int 	fd;
	
	char *line;
	while (i < 6)
	{
		fd = open(s[i], O_RDONLY);
		while ((line = get_next_line(fd)) != NULL) 
		{
			printf("%s", line);
			free(line);
		}
		close(fd);
		i++;
	}
	return (0);
}  */