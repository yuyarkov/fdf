/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:30:31 by dirony            #+#    #+#             */
/*   Updated: 2021/12/11 18:08:29 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom_img(int keycode, t_map_data *map_data)
{
	int	temp;
	int	scale;

	if (keycode == 69)
	{
		temp = map_data->zoom;
		map_data->zoom *= 1.2;
		if (temp == map_data->zoom)
			map_data->zoom++;
	}
	if (keycode == 78)
		map_data->zoom *= 0.8;
	if (map_data->zoom == 0)
		map_data->zoom = 1;
	if (map_data->height > map_data->max_alt)
		scale = map_data->height;
	else
		scale = map_data->max_alt;
	set_def_offsets(scale, map_data);
}

void	rotate_axe_z(int keycode, t_map_data *map_data)
{
	if (keycode == 2)
		map_data->rot_axe_z += PI_STEP;
	if (keycode == 0)
		map_data->rot_axe_z -= PI_STEP;
}

void	rotate_axe_x(int keycode, t_map_data *map_data)
{
	if (keycode == 1)
		map_data->rot_axe_x += PI_STEP;
	if (keycode == 13)
		map_data->rot_axe_x -= PI_STEP;
}

void	rotate_axe_y(int keycode, t_map_data *map_data)
{
	if (keycode == 12)
		map_data->rot_axe_y += PI_STEP;
	if (keycode == 14)
		map_data->rot_axe_y -= PI_STEP;
}

void	rotate_iso_img(int keycode, t_map_data *map_data)
{
	if (keycode == 88)
		map_data->rotation += PI_STEP;
	if (keycode == 86)
		map_data->rotation -= PI_STEP;
}
