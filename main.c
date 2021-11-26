/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 19:11:04 by dirony            #+#    #+#             */
/*   Updated: 2021/11/26 22:07:37 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*read_string_from_file(char *file_name)
{
	int		bytes_read;
	int		fd;
	char	*result;
	char	*temp;
	char	*buff;

	buff = malloc(BUFF_SIZE + 1);
	if (NULL == buff)
		return (NULL);
	fd = open(file_name, O_RDONLY);
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
	free(buff);
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

t_dot	**get_map_from_string(char *s, int width, int height)
{
	int		i;
	int		j;
	t_dot	**map;

	map = malloc(height * sizeof(t_dot *));
	i = 0;
	j = 0;
	while (i < height)
	{
		map[i] = malloc(width * sizeof(t_dot));
		if (*s == ' ')
		{
			s++;
			j++;
		}
		map[i][j].alt = ft_atoi(s);
		printf("map[%d][%d] = %d\n", i, j, map[i][j].alt);
		while (*s && *s != ' ' && *s != '\n')
			s++;
		if (*s && *s == '\n')
		{
			s++;
			i++;
			j = 0;
		}
	}
	return (map);
}

t_dot	**parse_map(char *file_name, int *width, int *height)
{
	char	*s;
	t_dot	**map;

	s = read_string_from_file(file_name);
	if (!s)
		return (NULL);
	printf("%s", s);
	*width = get_width(s);
	*height = get_height(s);
	map = get_map_from_string(s, *width, *height);

	return (NULL);
}

int	main(int argc, char **argv)
{
	//t_dot	*dot;
	t_dot	**map;
	int		width;
	int		height;
	int		i;
	int		j;

	if (argc < 1)
		return (0);
	width = 0;
	height = 0;
	map = parse_map(argv[1], &width, &height);

	i = 0;
	j = 0;
	printf("width: %d\n", width);
	printf("height: %d\n", height);
	while (map && map[i])
	{
		while (j < width)
		{
			printf("%d", map[i][j].alt);
			j++;
		}
		printf("\n");
		i++;
	}
	return (0);
}