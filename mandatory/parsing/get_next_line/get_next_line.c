/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozainan <yozainan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:02:57 by yozainan          #+#    #+#             */
/*   Updated: 2024/09/29 21:06:17 by yozainan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_new_line(char *tmp)
{
	int		i;
	char	*str;

	i = 0;
	if (!tmp[i])
		return (NULL);
	while (tmp[i] && tmp[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (tmp[i] && tmp[i] != '\n')
	{
		str[i] = tmp[i];
		i++;
	}
	if (tmp[i] == '\n')
	{
		str[i] = '\n';
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_handle(char *backup)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	k = i + 1;
	if (k >= (int)ft_strlen(backup) || !backup[k])
		return (free(backup), NULL);
	i++;
	str = malloc(sizeof(char) * ((ft_strlen(backup) - i) + 1));
	if (!str)
	{
		free(backup);
		return (NULL);
	}
	j = 0;
	while (i < (int)ft_strlen(backup) && backup[i])
		str[j++] = backup[i++];
	str[j] = '\0';
	free(backup);
	return (str);
}

static char	*read_file(int fd, char *tmp)
{
	char	*buffer;
	int		rbyts;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	rbyts = 1;
	while (!ft_strrch_finder(tmp, '\n') && rbyts != 0)
	{
		rbyts = read(fd, buffer, BUFFER_SIZE);
		if (rbyts == -1)
		{
			free(buffer);
			free(tmp);
			return (NULL);
		}
		buffer[rbyts] = '\0';
		tmp = ft_strjoin_l(tmp, buffer);
	}
	free(buffer);
	return (tmp);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = read_file(fd, tmp);
	if (!tmp)
		return (NULL);
	buff = get_new_line(tmp);
	tmp = ft_handle(tmp);
	return (buff);
}
