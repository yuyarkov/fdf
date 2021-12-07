/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 19:12:14 by dirony            #+#    #+#             */
/*   Updated: 2021/12/07 23:01:37 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
//
# include <stdio.h> //delete before submission
//



# define BUFF_SIZE 40096
# define DEF_COLOR 16777215 //white
# define MAX_W 1920
# define MAX_H 1080
# define M_LEFT 10
# define M_TOP 10
# define BASE_LOWER "0123456789abcdef"
# define BASE_UPPER "0123456789ABCDEF"

typedef struct s_dot
{
	int				alt;
	unsigned int	color;
}	t_dot;

typedef struct s_pixel
{
	int	x;
	int	y;
	int	color;
	int	delta_x;
	int	delta_y;
	int	sign_x;
	int	sign_y;
	int	error;
}	t_pixel;

typedef struct s_color
{
	int	a;
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_data {
	void	*mlx;
	void	*window;
	void	*img;
	char	*addr;
	int		bits_per_p;
	int		line_len;
	int		endian;
}	t_data;

typedef struct s_map_data
{
	char	*filename;
	int		height;
	int		width;
	int		max_alt;
	float	rotation;
	float	rot_axe_x;
	float	rot_axe_y;
	float	rot_axe_z;
	int		offset;
	int		v_offset;
	int		zoom;
	int		h_zoom;
	t_data	*pic;
	t_dot	**map;
}	t_map_data;

char	*read_string_from_file(char *file_name);
int		get_width(char *s);
int		get_height(char *s);
t_dot	**get_map_from_string(char *s, t_dot **map, t_map_data *map_data);
t_dot	**parse_map(char *file_name, t_map_data *map_data);
void	*clear_map(t_dot **map, int i);

size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *str, char ch);

char	*ft_atoi(char *s, t_dot *dot);
char	*ft_atoi_hex(char *s, t_dot *dot);

void	my_mlx_pixel_put(t_data *pic, int x, int y, int color);
void	get_delta(t_pixel *pixel1, t_pixel *pixel2);
int		get_gradient(t_pixel pixel1, t_pixel pixel2);
int		get_gradient_color(int color1, int color2, float progress);
void	draw_line(t_pixel pixel1, t_pixel pixel2, t_data *pic);
t_pixel	iso_pixel(t_pixel pixel, double z, t_map_data *map_data);
void	draw_iso_grid_h(t_dot **map, t_map_data *map_data, t_data *pic);
void	draw_iso_grid_v(t_dot **map, t_map_data *map_data, t_data *pic);

int		key_h(int keycode, t_map_data *map_data);
void	parse_keycode(int keycode, t_map_data *map_data);

void	zoom_img(int keycode, t_map_data *map_data);
void	rotate_axe_x(int keycode, t_map_data *map_data);
void	rotate_axe_y(int keycode, t_map_data *map_data);
void	rotate_axe_z(int keycode, t_map_data *map_data);
void	rotate_iso_img(int keycode, t_map_data *map_data);
void	move_img(int keycode, t_map_data *map_data);
void	set_default(t_map_data *map_data);
void	set_max_alt(t_dot **map, t_map_data *map_data);
void	draw_flat_h(t_dot **map, t_map_data *map_data, t_data *pic);
void	draw_flat_v(t_dot **map, t_map_data *map_data, t_data *pic);

#endif