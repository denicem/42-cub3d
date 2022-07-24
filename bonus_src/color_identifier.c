/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:01:58 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/24 22:25:08 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

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
		return (FAILURE);
	if (c == 'C')
	{
		if (data->check.c_identifier)
			return (2);
		data->c_colour = set_color;
		data->check.c_identifier = true;
	}
	else if (c == 'F')
	{
		if (data->check.f_identifier)
			return (2);
		data->f_colour = set_color;
		data->check.f_identifier = true;
	}
	return (SUCCESS);
}

static bool	check_syntax(char *str)
{
	int	count_commas;

	count_commas = 0;
	if (!ft_isdigit(*str))
		return (false);
	while (*str)
	{
		if (*str == ',' && ++count_commas > 2)
			return (false);
		if (!ft_isdigit(*str) && *str != ',')
			return (false);
		str++;
	}
	str--;
	if (!ft_isdigit(*str))
		return (false);
	return (true);
}

void	color_identifier(t_data *data, char c, char *c_code)
{
	char	**rgb;
	int		code;

	if (c != 'C' && c != 'F')
		exit_error(data, "Map identifier invalid.", FAILURE);
	if (!check_syntax(c_code))
		exit_error(data, "Color identifier invalid.", FAILURE);
	rgb = ft_split(c_code, ',');
	if (ft_strlen_arr((const char **) rgb) != 3)
	{
		ft_free_str_arr(&rgb);
		exit_error(data, "Color identifier invalid.", FAILURE);
	}
	code = set_color(data, (const char **) rgb, c);
	if (code == FAILURE)
	{
		ft_free_str_arr(&rgb);
		exit_error(data, "Color identifier must be between 0-255.", FAILURE);
	}
	else if (code == 2)
	{
		ft_free_str_arr(&rgb);
		exit_error(data, "Double color identifier.", FAILURE);
	}
	ft_free_str_arr(&rgb);
}
