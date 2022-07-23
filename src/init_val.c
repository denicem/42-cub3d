/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:21:55 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/23 23:53:49 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void check_open_space(t_data *data, char **map, int x, int y)
{
	if (!map[y - 1][x - 1] || !is_map_char(map[y - 1][x - 1])
		|| !map[y - 1][x] || !is_map_char(map[y - 1][x])
		|| !map[y - 1][x + 1] || !is_map_char(map[y - 1][x + 1])
		|| !map[y][x - 1] || !is_map_char(map[y][x - 1])
		|| !map[y][x + 1] || !is_map_char(map[y][x + 1])
		|| !map[y + 1][x - 1] || !is_map_char(map[y + 1][x - 1])
		|| !map[y + 1][x] || !is_map_char(map[y + 1][x])
		|| !map[y + 1][x + 1] || !is_map_char(map[y + 1][x + 1]))
		exit_error(data, "Open space not closed/surrounded by walls.", FAIL);
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

static void check_border(t_data *data)
{
	int	x;

	x = 0;
	while ((data->map)[0][x])
	{
		if ((data->map)[0][x] == '0')
			exit_error(data, "Open space not closed/surrounded by walls.",
				FAIL);
		x++;
	}
	x = 0;
	while ((data->map)[data->map_height - 1][x])
	{
		if ((data->map)[data->map_height - 1][x] == '0')
			exit_error(data, "Open space not closed/surrounded by walls.",
				FAIL);
		x++;
	}
}

static void check_player(t_data *data)
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
		exit_error(data, "No player located.", FAIL);
	else if (count > 1)
		exit_error(data, "Too many players located.", FAIL);
}

void	map_parser(t_data *data)
{
	check_player(data);
	check_border(data);
	check_surroundings(data);
}

void	init_val(t_data *data)
{
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		exit_error(data, "Malloc failed.", FAIL);
	create_map(data);
	map_parser(data);
	set_player(data);
}
