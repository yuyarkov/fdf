/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:35:22 by dirony            #+#    #+#             */
/*   Updated: 2021/12/06 22:17:02 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *pic, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && x < (MAX_W - M_LEFT) && y > 0 && y < (MAX_H - M_TOP))
	{
		dst = pic->addr + (y * pic->line_length + x * (pic->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void drawLine(t_pixel pixel1, t_pixel pixel2, t_data *pic, int color)
{
	int deltaX = abs(pixel2.x - pixel1.x);
    int deltaY = abs(pixel2.y - pixel1.y);
    int signX = pixel1.x < pixel2.x ? 1 : -1;
    int signY = pixel1.y < pixel2.y ? 1 : -1;
    int error = deltaX - deltaY;

    while(pixel1.x != pixel2.x || pixel1.y != pixel2.y)
    {
		if ((pixel1.x < 0 && pixel1.x > (MAX_W - M_LEFT)) || (pixel1.y < 0 && pixel1.y > (MAX_H - M_TOP)))
			break;
		my_mlx_pixel_put(pic, pixel1.x, pixel1.y, color);
        int error2 = error * 2;
        if(error2 > -deltaY)
        {
            error -= deltaY;
            pixel1.x += signX;
        }
        if(error2 < deltaX)
        {
            error += deltaX;
            pixel1.y += signY;
        }
    }
}


t_pixel	iso_pixel(t_pixel pixel, double z, t_map_data *map_data)
{
	t_pixel result;
	float	x;
	float	y;
	float	x2;
	float	y2;
	float	iso_angle;
	float	angle_z;
	float	angle_x;
	float	angle_y;

	iso_angle = map_data->rotation; //0.6;// 0.523599
	angle_x = map_data->rotate_axe_x;
	angle_y = map_data->rotate_axe_y;
	angle_z = map_data->rotate_axe_z;
	x = pixel.x * cos(angle_z) + pixel.y * sin(angle_z);
	y = -pixel.x * sin(angle_z) + pixel.y * cos(angle_z);
	y2 = y * cos(angle_x) + z * sin(angle_x);
	z = -y * sin(angle_x) + z * cos(angle_x);
	y = y2;
	x2 = x * cos(angle_y) + z * sin(angle_y);
	z = -x * sin(angle_y) + z * cos(angle_y);
	x = x2;
	result.x = -(x - y) * map_data->zoom * cos(iso_angle) + map_data->offset;
	result.y = (x + y) * map_data->zoom * sin(iso_angle) - z * map_data->zoom + map_data->v_offset;
	return (result);
}

void	draw_iso_grid(t_dot **map, t_map_data *map_data, t_data *pic)
{
	int	i;
	int	j;
	int	color;
	t_pixel pixel1;
	t_pixel pixel2;

	i = 0;
	color = DEF_COLOR;
 	while (i < map_data->height - 1)
 	{
  		j = 0;
  		while (j < map_data->width)
  		{
			pixel1.x = i;
			pixel1.y = j;
			pixel1 = iso_pixel(pixel1, map[i][j].alt, map_data);
			pixel2.x = i + 1;
			pixel2.y = j;
			pixel2 = iso_pixel(pixel2, map[i + 1][j].alt, map_data);
			if (map[i][j].color == map[i + 1][j].color)
				color = map[i][j].color;
			drawLine(pixel1, pixel2, pic, color);
			j++;
  		}
  		i++;
	}
	i = 0;
	while (i < map_data->height)
 	{
  		j = 0;
  		while (j < map_data->width - 1)
  		{
			pixel1.x = i;
			pixel1.y = j;
			pixel1 = iso_pixel(pixel1, map[i][j].alt, map_data);
			pixel2.x = i;
			pixel2.y = j + 1;
			pixel2 = iso_pixel(pixel2, map[i][j + 1].alt, map_data);
			if (map[i][j].color == map[i][j + 1].color)
				color = map[i][j].color;
   			drawLine(pixel1, pixel2, pic, color);
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
