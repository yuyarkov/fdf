/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 22:18:54 by dirony            #+#    #+#             */
/*   Updated: 2021/12/06 22:21:11 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	parse_keycode(int keycode, t_map_data *map_data)
{
	if (keycode == 53)
	{
		clear_map(map_data->map, map_data->height);
		exit (1);//проверить утечки
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
	pic->addr = mlx_get_data_addr(pic->img, &pic->bits_per_pixel,
			&pic->line_length, &pic->endian);
	draw_iso_grid(map, map_data, pic);
	mlx_put_image_to_window(pic->mlx, pic->window, pic->img,
		M_LEFT, M_TOP);
	return (0);
}
