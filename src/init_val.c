/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:21:55 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/20 16:43:48 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <stdio.h>

void	init_val(t_data *data)
{
	// allocate memory for structs
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		exit(FAIL); //alloc failed

	// create_map(data);

	// setting up player starting position
	data->player->pos.x = 5;
	data->player->pos.y = 2;

	data->player->dir.x = 0;
	data->player->dir.y = 1;

	data->player->plane.x = 0.66;
	data->player->plane.y = 0;
}
