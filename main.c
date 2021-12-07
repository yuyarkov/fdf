/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 19:11:04 by dirony            #+#    #+#             */
/*   Updated: 2021/12/07 22:23:04 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_data	*create_pic(t_map_data *map_data)
{
	t_data	*pic;

	pic = malloc(sizeof(t_data));
	if (NULL == pic)
		return (NULL);
	pic->mlx = mlx_init();
	pic->window = mlx_new_window(pic->mlx, MAX_W, MAX_H, map_data->filename);
	pic->img = mlx_new_image(pic->mlx, MAX_W, MAX_H);
	pic->addr = mlx_get_data_addr(pic->img, &pic->bits_per_p,
			&pic->line_len, &pic->endian);
	return (pic);
}

void	mlx_run(t_dot **map, t_map_data *map_data)
{
	t_data	*pic;

	map_data->map = map;
	pic = create_pic(map_data);
	map_data->pic = pic;
	mlx_hook(pic->window, 02, (1L << 0), &key_h, map_data);
	draw_iso_grid_h(map, map_data, pic);
	draw_iso_grid_v(map, map_data, pic);
	mlx_put_image_to_window(pic->mlx, pic->window, pic->img, M_LEFT, M_TOP);
	mlx_loop(pic->mlx);
	free(pic);
}

void	*clear_map(t_dot **map, int i)
{
	while (i - 1)
	{
		free(map[i - 1]);
		i--;
	}
	free(map[0]);
	free(map);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_dot		**map;
	t_map_data	*map_data;

	if (argc < 1)
		return (0);
	map_data = malloc(sizeof(t_map_data));
	if (NULL == map_data)
		return (0);
	map = parse_map(argv[1], map_data);
	if (!map)
		return (0);
	mlx_run(map, map_data);
	return (0);
}
