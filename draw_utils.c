/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:35:22 by dirony            #+#    #+#             */
/*   Updated: 2021/12/11 15:41:14 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *pic, int x, int y, int color)
{
	char	*dest;

	if (x > 0 && x < (MAX_W - M_LEFT) && y > 0 && y < (MAX_H - M_TOP))
	{
		dest = pic->addr + (y * pic->line_len + x * (pic->bits_per_p / 8));
		*(unsigned int *)dest = color;
	}
}

void	get_delta(t_pixel *pixel1, t_pixel *pixel2)
{
	if (pixel1->x < pixel2->x)
		pixel1->sign_x = 1;
	else
		pixel1->sign_x = -1;
	if (pixel1->y < pixel2->y)
		pixel1->sign_y = 1;
	else
		pixel1->sign_y = -1;
	pixel1->delta_x = abs(pixel2->x - pixel1->x);
	pixel1->delta_y = abs(pixel2->y - pixel1->y);
	pixel1->error = pixel1->delta_x - pixel1->delta_y;
}

void	draw_line(t_pixel pixel1, t_pixel pixel2, t_data *pic)
{
	int	color;

	get_delta(&pixel1, &pixel2);
	while (pixel1.x != pixel2.x || pixel1.y != pixel2.y)
	{
		color = get_gradient(pixel1, pixel2);
		my_mlx_pixel_put(pic, pixel1.x, pixel1.y, color);
		pixel2.error = pixel1.error * 2;
		if (pixel2.error > -pixel1.delta_y)
		{
			pixel1.error -= pixel1.delta_y;
			pixel1.x += pixel1.sign_x;
		}
		if (pixel2.error < pixel1.delta_x)
		{
			pixel1.error += pixel1.delta_x;
			pixel1.y += pixel1.sign_y;
		}
	}
}

int	get_gradient(t_pixel pixel1, t_pixel pixel2)
{
	float	progress;
	int		orig_dist;
	int		curr_dist;

	orig_dist = sqrt(pixel1.delta_x * pixel1.delta_x
			+ pixel1.delta_y * pixel1.delta_y);
	curr_dist = sqrt((pixel1.x - pixel2.x) * (pixel1.x - pixel2.x)
			+ (pixel1.y - pixel2.y) * (pixel1.y - pixel2.y));
	progress = (float)curr_dist / orig_dist;
	return (get_gradient_color(pixel1.color, pixel2.color, progress));
}

int	get_gradient_color(int color1, int color2, float progress)
{
	t_color	col1;
	t_color	col2;
	t_color	res;
	float	left;

	col1.a = (color1 & 0xff000000) >> 24;
	col1.r = (color1 & 0x00ff0000) >> 16;
	col1.g = (color1 & 0x0000ff00) >> 8;
	col1.b = color1 & 0x000000ff;
	col2.a = (color2 & 0xff000000) >> 24;
	col2.r = (color2 & 0x00ff0000) >> 16;
	col2.g = (color2 & 0x0000ff00) >> 8;
	col2.b = color2 & 0x000000ff;
	left = (1 - progress);
	res.a = (int)(col1.a * progress + col2.a * left);
	res.r = (int)(col1.r * progress + col2.r * left);
	res.g = (int)(col1.g * progress + col2.g * left);
	res.b = (int)(col1.b * progress + col2.b * left);
	return ((res.a << 24) + (res.r << 16) + (res.g << 8) + res.b);
}
