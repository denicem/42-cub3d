/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:21:55 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/24 20:26:09 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_val(t_data *data)
{
	create_map(data);
	map_parser(data);
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		exit_error(data, "Malloc failed.", FAILURE);
	set_player(data);
}
