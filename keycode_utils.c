/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 22:18:54 by dirony            #+#    #+#             */
/*   Updated: 2021/12/11 19:41:14 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_and_exit(t_map_data *map_data)
{
	t_data	*pic;

	pic = map_data->pic;
	clear_map(map_data->map, map_data->height);
	mlx_destroy_image(pic->mlx, pic->img);
	free(map_data);
	exit (1);
}

void	parse_keycode(int keycode, t_map_data *map_data)
{
	if (keycode == 53)
		free_and_exit(map_data);
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
	{
		map_data->iso_projection = 1;
		set_def_position(map_data);
	}
	if (keycode == 19)
	{
		map_data->iso_projection = 0;
		set_def_position(map_data);
	}
}

void	set_def_offsets(int scale, t_map_data *map_data)
{
	map_data->adj_x = map_data->width / 2;
	map_data->adj_y = map_data->height / 2;
	map_data->offset = (MAX_W - map_data->width * map_data->zoom) / 2;
	if ((map_data->max_alt + map_data->height) > MAX_H / 5)
		map_data->h_zoom = (map_data->max_alt + map_data->height) * 9 / MAX_H;
	else
		map_data->h_zoom = 1;
	if (map_data->iso_projection)
		map_data->v_offset = abs(MAX_H - scale * map_data->h_zoom
				+ map_data->height * map_data->zoom) / 2;
	else
		map_data->v_offset = (MAX_H - map_data->height * map_data->zoom) / 2;
}

void	set_def_position(t_map_data *map_data)
{
	int	scale;

	if (map_data->height > map_data->max_alt)
		scale = map_data->height;
	else
		scale = map_data->max_alt;
	map_data->rot_axe_x = 0;
	map_data->rot_axe_y = 0;
	if (map_data->iso_projection)
		map_data->rot_axe_z = -1.57079632679;
	else
		map_data->rot_axe_z = 0;
	if (MAX_H / scale > MAX_W / map_data->width)
		map_data->zoom = MAX_H / (scale * 4);
	else
		map_data->zoom = MAX_W / (map_data->width * 4);
	if (map_data->zoom < 1)
		map_data->zoom = 1;
	set_def_offsets(scale, map_data);
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
	if (map_data->iso_projection == 0)
	{
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
