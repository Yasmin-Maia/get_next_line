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
	if (bag[i] == '\0')
		return (free(bag), NULL);
	//printf ("bag: %s :bag ", bag);
	if (bag[i] == '\n' || bag[i] == '\0')
	{
		new_bag = ft_strdup(&bag[i + 1]);
		//printf ("new_bag: %s :new_bag ", new_bag);
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

	buffer = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (read_file(bag) == 0 && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(bag), NULL);
		backup = ft_strjoin(bag, buffer);
		if (!backup)
			return (free(buffer), free(bag), NULL);
		free(bag);
		bag = backup;
	}
	return (free(buffer), bag);
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
	line = ft_calloc(sizeof(char), (i + 2));
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
	static char	*bag;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!bag)
		bag = ft_strdup("");
	bag = get_line(fd, bag);
	if (!bag)
		return (NULL);
	line = write_line(bag);
	bag = remove_read_line(bag);
	if (!line)
		return (NULL);
	return (line);
}


int main(void)
{
	int fd = open("giant_line_nl.txt", O_RDONLY);
	
	char *line;
	while ((line = get_next_line(fd)) != NULL) 
	{
		printf("%s", line);
		free(line);
	}

	close(fd);
	return (0);
}