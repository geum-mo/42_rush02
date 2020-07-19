/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dict.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekang <gekang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 19:51:46 by donghwki          #+#    #+#             */
/*   Updated: 2020/07/19 18:00:20 by gekang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush_02.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

char	*read_buf(char *file, char *dest)
{
	int		i;
	int		j;
	char	buf[BUF_SIZE];
	int		buf_len;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		g_flag |= 0x2100;
		return (0);
	}
	j = 0;
	while ((buf_len = read(fd, buf, BUF_SIZE)))
	{
		i = 0 - 1;
		while (++i < buf_len)
			dest[i + j * BUF_SIZE] = buf[i];
		j++;
	}
	close(fd);
	return (dest);
}

char	*get_dict_buf(char *file)
{
	char	buf[BUF_SIZE];
	int		buf_len;
	int		size;
	int		fd;
	char	*dest;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		g_flag = g_flag | 0x2100;
		return (0);
	}
	size = 0;
	while ((buf_len = read(fd, buf, BUF_SIZE)))
		size += buf_len;
	close(fd);
	if (!(dest = (char *)malloc(sizeof(char) * size + 1)))
		return (0);
	dest = read_buf(file, dest);
	dest[size] = 0;
	return (dest);
}

int		trim_dict(char **split, int size)
{
	int		i;
	char	*temp;

	i = 0 - 1;
	while (++i < size)
	{
		if (!(temp = ft_trim(split[i])))
			return (0);
		free(split[i]);
		if (!(split[i] = ft_strdup(temp, 0, ft_strlen(temp))))
		{
			free_dict_split(split, size);
			free(temp);
			return (0);
		}
		free(temp);
	}
	return (1);
}

int		key_val_init(char *line, int num, t_dict *dict)
{
	int		start;
	int		end;
	char	*tmp;

	start = 0;
	end = start;
	while (line[end] && line[end] != ':')
		end++;
	if (!(tmp = ft_strdup(line, start, end)))
		return (0);
	dict->key[num] = ft_trim(tmp);
	free(tmp);
	start = end + 1;
	end = start;
	while (line[end])
		end++;
	if (!(tmp = ft_strdup(line, start, end)))
		return (0);
	dict->value[num] = ft_trim(tmp);
	free(tmp);
	return (1);
}

t_dict	*dict_init(char **dict_split_lines, int dict_size)
{
	t_dict	*new_dict;
	int		i;

	if (!(new_dict = (t_dict *)malloc(sizeof(t_dict) * 1)))
	{
		g_flag |= 0x10;
		return (0);
	}
	new_dict->size = dict_size;
	if (!(new_dict->key = (char **)malloc(sizeof(char *) * dict_size)))
	{
		g_flag |= 0x20;
		return (0);
	}
	if (!(new_dict->value = (char **)malloc(sizeof(char *) * dict_size)))
	{
		g_flag |= 0x40;
		return (0);
	}
	i = 0 - 1;
	while (++i < dict_size)
		if (!(key_val_init(dict_split_lines[i], i, new_dict)))
			g_flag |= 0x80;
	return (new_dict);
}
