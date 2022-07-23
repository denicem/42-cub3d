/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:01:58 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/23 18:33:38 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static bool	check_color(int color)
{
	if (color >= 0 && color <= 255)
		return (true);
	return (false);
}

static int	set_color(t_data *data, const char **rgb, char c)
{
	t_colour	set_color;

	set_color.red = ft_atoi(rgb[0]);
	set_color.green = ft_atoi(rgb[1]);
	set_color.blue = ft_atoi(rgb[2]);
	if (!check_color(set_color.red) || !check_color(set_color.green)
		|| !check_color(set_color.blue))
		return (FAIL);
	if (c == 'C')
	{
		data->c_colour = set_color;
		data->check.c_identifier = true;
	}
	else if (c == 'F')
	{
		data->f_colour = set_color;
		data->check.f_identifier = true;
	}
	return (SUCC);
}

static bool	check_syntax(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != ',')
			return (false);
		str++;
	}
	return (true);
}

void	color_identifier(t_data *data, char c, char *c_code)
{
	char	**rgb;

	if (!check_syntax(c_code))
		exit_error(data, "Color identifier invalid.", FAIL);
	rgb = ft_split(c_code, ',');
	if (ft_strlen_arr((const char **) rgb) != 3)
	{
		ft_free_str_arr(&rgb);
		exit_error(data, "Color identifier invalid.", FAIL);
	}
	if (set_color(data, (const char **) rgb, c) == FAIL)
	{
		ft_free_str_arr(&rgb);
		exit_error(data, "Color identifier must be between 0-255.", FAIL);
	}
	ft_free_str_arr(&rgb);
}
