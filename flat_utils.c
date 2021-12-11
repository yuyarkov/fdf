/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flat_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:25:06 by dirony            #+#    #+#             */
/*   Updated: 2021/12/11 19:21:06 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pixel	rotate_flat(t_pixel pixel, t_map_data *m)
{
	t_pixel	result;
	int		adj_x;
	int		adj_y;

	adj_x = MAX_W / 2;
	adj_y = MAX_H / 2;
	result.x = -(pixel.x - adj_x) * cos(m->rot_axe_z)
		+ (pixel.y - adj_y) * sin(m->rot_axe_z) + adj_x;
	result.y = (pixel.x - adj_x) * sin(m->rot_axe_z)
		+ (pixel.y - adj_y) * cos(m->rot_axe_z) + adj_y;
	result.color = pixel.color;
	return (result);
}

void	draw_flat_h(t_dot **map, t_map_data *map_data, t_data *pic)
{
	int		i;
	int		j;
	t_pixel	pixel1;
	t_pixel	pixel2;

	i = 0;
	while (i < map_data->height - 1)
	{
		j = 0;
		while (j < map_data->width)
		{
			pixel1.x = i * map_data->zoom + map_data->offset;
			pixel1.y = j * map_data->zoom + map_data->v_offset;
			pixel1.color = map[i][j].color;
			pixel2.x = (i + 1) * map_data->zoom + map_data->offset;
			pixel2.y = j * map_data->zoom + map_data->v_offset;
			pixel2.color = map[i + 1][j].color;
			pixel1 = rotate_flat(pixel1, map_data);
			pixel2 = rotate_flat(pixel2, map_data);
			draw_line(pixel1, pixel2, pic);
			j++;
		}
		i++;
	}
}

void	draw_flat_v(t_dot **map, t_map_data *map_data, t_data *pic)
{
	int		i;
	int		j;
	t_pixel	pixel1;
	t_pixel	pixel2;

	i = 0;
	while (i < map_data->height)
	{
		j = 0;
		while (j < map_data->width - 1)
		{
			pixel1.x = i * map_data->zoom + map_data->offset;
			pixel1.y = j * map_data->zoom + map_data->v_offset;
			pixel1.color = map[i][j].color;
			pixel2.x = i * map_data->zoom + map_data->offset;
			pixel2.y = (j + 1) * map_data->zoom + map_data->v_offset;
			pixel2.color = map[i][j + 1].color;
			pixel1 = rotate_flat(pixel1, map_data);
			pixel2 = rotate_flat(pixel2, map_data);
			draw_line(pixel1, pixel2, pic);
			j++;
		}
		i++;
	}
}
