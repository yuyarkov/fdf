/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:30:31 by dirony            #+#    #+#             */
/*   Updated: 2021/12/07 20:26:54 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom_img(int keycode, t_map_data *map_data)
{
	int	temp;

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
}

void	rotate_axe_z(int keycode, t_map_data *map_data)
{
	if (keycode == 2)
		map_data->rot_axe_z += 0.19635;
	if (keycode == 0)
		map_data->rot_axe_z -= 0.19635;
}

void	rotate_axe_x(int keycode, t_map_data *map_data)
{
	if (keycode == 1)
		map_data->rot_axe_x += 0.19635;
	if (keycode == 13)
		map_data->rot_axe_x -= 0.19635;
}

void	rotate_axe_y(int keycode, t_map_data *map_data)
{
	if (keycode == 12)
		map_data->rot_axe_y += 0.19635;
	if (keycode == 14)
		map_data->rot_axe_y -= 0.19635;
}

void	rotate_iso_img(int keycode, t_map_data *map_data)
{
	if (keycode == 88)
		map_data->rotation += 0.19635;
	if (keycode == 86)
		map_data->rotation -= 0.19635;
}
