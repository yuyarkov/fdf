/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 19:49:23 by dirony            #+#    #+#             */
/*   Updated: 2021/12/07 22:22:01 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*read_string_from_file(char *file_name)
{
	int		bytes_read;
	int		fd;
	char	*result;
	char	*temp;
	char	buff[BUFF_SIZE + 1];

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (NULL);
	bytes_read = read(fd, buff, BUFF_SIZE);
	buff[bytes_read] = '\0';
	result = ft_strdup(buff);
	while (bytes_read)
	{
		temp = result;
		bytes_read = read(fd, buff, BUFF_SIZE);
		buff[bytes_read] = '\0';
		result = ft_strjoin(temp, buff);
		free(temp);
	}
	close(fd);
	return (result);
}

int	get_width(char *s)
{
	int	flag;
	int	counter;

	flag = 1;
	counter = 0;
	while (*s && *s != '\n')
	{
		if (*s != ' ')
		{
			if (flag)
			{
				counter++;
				flag = 0;
			}
		}
		if (*s == ' ')
			flag = 1;
		s++;
	}
	return (counter);
}

int	get_height(char *s)
{
	int	counter;

	counter = 0;
	while (s && *s)
	{
		s = ft_strchr(s, '\n');
		counter++;
		if (s)
			s++;
	}
	return (counter);
}

t_dot	**get_map_from_string(char *s, t_dot **map, t_map_data *map_data)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	temp = s;
	while (i < map_data->height)
	{
		map[i] = malloc(map_data->width * sizeof(t_dot));
		if (NULL == map[i])
			return (clear_map(map, i));
		j = 0;
		while (j < map_data->width)
		{
			s = ft_atoi(s, &map[i][j]);
			if (*s == ',')
				s = ft_atoi_hex(s + 1, &map[i][j]);
			else
				map[i][j].color = DEF_COLOR;
			j++;
		}
		i++;
	}
	free(temp);
	return (map);
}

t_dot	**parse_map(char *file_name, t_map_data *map_data)
{
	char	*s;
	t_dot	**map;

	map_data->filename = file_name;
	s = read_string_from_file(file_name);
	if (!s)
		return (NULL);
	map_data->width = get_width(s);
	map_data->height = get_height(s);
	map = malloc(map_data->height * sizeof(t_dot *));
	if (NULL == map)
		return (NULL);
	map = get_map_from_string(s, map, map_data);
	set_max_alt(map, map_data);
	set_default(map_data);
	return (map);
}
