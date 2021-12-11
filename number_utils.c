/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:50:14 by dirony            #+#    #+#             */
/*   Updated: 2021/12/11 14:46:49 by dirony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_isdigit(char ch)
{
	if ((ch >= '0') && (ch <= '9'))
		return (1);
	else
		return (0);
}

char	*ft_atoi(char *s, t_dot *dot)
{
	int	result;
	int	sign;

	while (*s == ' ')
		s++;
	sign = 1;
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	result = 0;
	while (ft_isdigit(*s))
	{
		result = result * 10;
		result = result + *s - 48;
		s++;
	}
	dot->alt = result * sign;
	if (*s == '\n')
		s++;
	return (s);
}

int	get_hex_digit(char ch)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (ch == BASE_LOWER[i] || ch == BASE_UPPER[i])
			return (i);
		i++;
	}
	return (0);
}

int	ft_is_hexdigit(char ch)
{
	if (ft_strchr(BASE_LOWER, ch) || ft_strchr(BASE_UPPER, ch))
		return (1);
	else
		return (0);
}

char	*ft_atoi_hex(char *s, t_dot *dot)
{
	unsigned int	result;

	if (*s == '0' && (*(s + 1) == 'x' || *(s + 1) == 'X'))
		s += 2;
	result = 0;
	while (ft_is_hexdigit(*s))
	{
		result = result * 16;
		result = result + get_hex_digit(*s);
		s++;
	}
	dot->color = result;
	if (*s == '\n')
		s++;
	return (s);
}
