/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:21:55 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/23 19:20:54 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"



void	map_parser(t_data *data)
{
	char **map;

	map = data->map;
	
}

void	init_val(t_data *data)
{
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		exit_error(data, "Malloc failed.", FAIL);
	create_map(data);
	//parse map
	set_player(data);
}
