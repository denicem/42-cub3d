/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:21:55 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/23 22:08:30 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
		exit_error(data, "No player located.", FAIL);
	else if (count > 1)
		exit_error(data, "Too many players located.", FAIL);
}

void	map_parser(t_data *data)
{
	check_player(data);
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
