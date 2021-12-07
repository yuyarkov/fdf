/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 22:18:54 by dirony            #+#    #+#             */
/*   Updated: 2021/12/07 23:17:11 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	parse_keycode(int keycode, t_map_data *map_data)
{
	if (keycode == 53)
	{
		clear_map(map_data->map, map_data->height);
		free(map_data);
		exit (1);
	}
	if (keycode >= 123 && keycode <= 126)
		move_img(keycode, map_data);
	if (keycode == 69 || keycode == 78)
		zoom_img(keycode, map_data);
	if (keycode == 88 || keycode == 86)
		rotate_iso_img(keycode, map_data);
	if (keycode == 2 || keycode == 0)
		rotate_axe_z(keycode, map_data);
	if (keycode == 13 || keycode == 1)
		rotate_axe_x(keycode, map_data);
	if (keycode == 12 || keycode == 14)
		rotate_axe_y(keycode, map_data);
	if (keycode == 18)
		set_default(map_data);
}

void	set_default(t_map_data *map_data)
{
	int	scale;

	if (map_data->height > map_data->max_alt)
		scale = map_data->height + 50;
	else
		scale = map_data->max_alt + 50;
	map_data->rot_axe_x = 0;
	map_data->rot_axe_y = 0;
	map_data->rot_axe_z = -1.6;
	map_data->zoom = MAX_H / (scale);
	if (map_data->zoom < 1)
		map_data->zoom = 1;
	map_data->offset = (MAX_W - map_data->width * map_data->zoom) / 2;
	map_data->v_offset = (MAX_H - map_data->max_alt * map_data->zoom) * 2;
	if ((map_data->max_alt + map_data->height) > MAX_H / 5)
		map_data->h_zoom = (map_data->max_alt + map_data->height) * 9 / MAX_H;
	else
		map_data->h_zoom = 1;
	// printf("v_offset: %d, height: %d, max_alt: %d, h_zoom: %d\n", map_data->v_offset,
	// 	map_data->height, map_data->max_alt, map_data->h_zoom);
	map_data->rotation = 0.52;
}

int	key_h(int keycode, t_map_data *map_data)
{
	t_dot	**map;
	t_data	*pic;

	map = map_data->map;
	pic = map_data->pic;
	parse_keycode(keycode, map_data);
	mlx_destroy_image(pic->mlx, pic->img);
	pic->img = mlx_new_image(pic->mlx, MAX_W, MAX_H);
	pic->addr = mlx_get_data_addr(pic->img, &pic->bits_per_p,
			&pic->line_len, &pic->endian);
	if (keycode == 19)
	{
		set_default(map_data);
		draw_flat_h(map, map_data, pic);
		draw_flat_v(map, map_data, pic);
	}
	else
	{
		draw_iso_grid_h(map, map_data, pic);
		draw_iso_grid_v(map, map_data, pic);
	}
	mlx_put_image_to_window(pic->mlx, pic->window, pic->img,
		M_LEFT, M_TOP);
	return (0);
}

void	draw_flat_h(t_dot **map, t_map_data *map_data, t_data *pic)
{
	int		i;
	int		j;
	t_pixel	pixel1;
	t_pixel	pixel2;

	map_data->v_offset = (MAX_H - map_data->height * map_data->zoom) / 2;
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
			draw_line(pixel1, pixel2, pic);
			j++;
		}
		i++;
	}
}
