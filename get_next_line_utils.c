/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasmin <yasmin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:40:29 by yasmin            #+#    #+#             */
/*   Updated: 2024/12/17 16:30:14 by yasmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	j = 0;
	temp = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (temp == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		temp[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		temp[i] = s2[j];
		i++;
		j++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = (char *)malloc(ft_strlen(s1) + 1);
	if (ptr == NULL)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*temp;

	if (s == NULL)
		return (NULL);
	i = 0;
	slen = ft_strlen(s);
	if (start >= slen || len == 0)
		return (ft_strdup(""));
	if (start + len > slen)
		len = slen - start;
	temp = malloc(sizeof(char) * (len + 1));
	if (temp == NULL)
		return (NULL);
	while (i < len)
	{
		temp[i] = s[start + i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
