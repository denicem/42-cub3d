/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:37:06 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/24 19:19:36 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	check_open_space(t_data *data, char **map, int x, int y)
{
	if (!map[y - 1][x - 1] || !is_map_char(map[y - 1][x - 1])
		|| !map[y - 1][x] || !is_map_char(map[y - 1][x])
		|| !map[y - 1][x + 1] || !is_map_char(map[y - 1][x + 1])
		|| !map[y][x - 1] || !is_map_char(map[y][x - 1])
		|| !map[y][x + 1] || !is_map_char(map[y][x + 1])
		|| !map[y + 1][x - 1] || !is_map_char(map[y + 1][x - 1])
		|| !map[y + 1][x] || !is_map_char(map[y + 1][x])
		|| !map[y + 1][x + 1] || !is_map_char(map[y + 1][x + 1]))
		exit_error(data, "Open space not closed/surrounded by walls.", FAILURE);
}

static void	check_surroundings(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while ((data->map)[y])
	{
		x = 0;
		while ((data->map)[y][x])
		{
			if ((data->map)[y][x] == '0' || is_player_char((data->map)[y][x]))
				check_open_space(data, data->map, x, y);
			x++;
		}
		y++;
	}
}

static void	check_border(t_data *data)
{
	int	x;

	x = 0;
	while ((data->map)[0][x])
	{
		if ((data->map)[0][x] == '0' || is_player_char((data->map)[0][x]))
			exit_error(data, "Open space not closed/surrounded by walls.",
				FAILURE);
		x++;
	}
	x = 0;
	while ((data->map)[data->map_height - 1][x])
	{
		if ((data->map)[data->map_height - 1][x] == '0'
			|| is_player_char((data->map)[0][x]))
			exit_error(data, "Open space not closed/surrounded by walls.",
				FAILURE);
		x++;
	}
}

static void	check_player(t_data *data)
{
	int	count;
	int	x;
	int	y;

	count = 0;
	y = 0;
	while ((data->map)[y])
	{
		x = 0;
		while ((data->map)[y][x])
		{
			if (is_player_char((data->map)[y][x]))
				count++;
			x++;
		}
		y++;
	}
	if (count < 1)
		exit_error(data, "No player located.", FAILURE);
	else if (count > 1)
		exit_error(data, "Too many players located.", FAILURE);
}

void	map_parser(t_data *data)
{
	check_player(data);
	check_border(data);
	check_surroundings(data);
}
