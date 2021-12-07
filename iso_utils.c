/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 20:11:36 by dirony            #+#    #+#             */
/*   Updated: 2021/12/07 23:06:36 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pixel	iso_pixel(t_pixel pixel, double z, t_map_data *map_data)
{
	t_pixel	result;
	float	x;
	float	y;
	float	x2;
	float	y2;

	x = pixel.x * cos(map_data->rot_axe_z)
		+ pixel.y * sin(map_data->rot_axe_z);
	y = -pixel.x * sin(map_data->rot_axe_z)
		+ pixel.y * cos(map_data->rot_axe_z);
	y2 = y * cos(map_data->rot_axe_x) + z * sin(map_data->rot_axe_x);
	z = -y * sin(map_data->rot_axe_x) + z * cos(map_data->rot_axe_x);
	y = y2;
	x2 = x * cos(map_data->rot_axe_y) + z * sin(map_data->rot_axe_y);
	z = -x * sin(map_data->rot_axe_y) + z * cos(map_data->rot_axe_y);
	x = x2;
	result.x = -(x - y) * map_data->zoom * cos(map_data->rotation)
		+ map_data->offset;
	result.y = (x + y) * map_data->zoom * sin(map_data->rotation)
		- (z * map_data->zoom / map_data->h_zoom) + map_data->v_offset;
	return (result);
}

void	draw_iso_grid_h(t_dot **map, t_map_data *map_data, t_data *pic)
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
			pixel1.x = i;
			pixel1.y = j;
			pixel1 = iso_pixel(pixel1, map[i][j].alt, map_data);
			pixel1.color = map[i][j].color;
			pixel2.x = i + 1;
			pixel2.y = j;
			pixel2 = iso_pixel(pixel2, map[i + 1][j].alt, map_data);
			pixel2.color = map[i + 1][j].color;
			draw_line(pixel1, pixel2, pic);
			j++;
		}
		i++;
	}
}

void	draw_iso_grid_v(t_dot **map, t_map_data *map_data, t_data *pic)
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
			pixel1.x = i;
			pixel1.y = j;
			pixel1 = iso_pixel(pixel1, map[i][j].alt, map_data);
			pixel1.color = map[i][j].color;
			pixel2.x = i;
			pixel2.y = j + 1;
			pixel2 = iso_pixel(pixel2, map[i][j + 1].alt, map_data);
			pixel2.color = map[i][j + 1].color;
			draw_line(pixel1, pixel2, pic);
			j++;
		}
		i++;
	}
}

void	move_img(int keycode, t_map_data *map_data)
{
	if (keycode == 124)
		map_data->offset += 20;
	if (keycode == 123)
		map_data->offset += -20;
	if (keycode == 126)
		map_data->v_offset += -20;
	if (keycode == 125)
		map_data->v_offset += 20;
}

void	set_max_alt(t_dot **map, t_map_data *map_data)
{
	int	i;
	int	j;
	int	max_alt;

	i = 0;
	max_alt = 0;
	while (i < map_data->height)
	{
		j = 0;
		while (j < map_data->width)
		{
			if (map[i][j].alt > max_alt)
				max_alt = map[i][j].alt;
			j++;
		}
		i++;
	}
	map_data->max_alt = max_alt;
}
