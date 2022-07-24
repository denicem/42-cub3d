/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:21:55 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/24 16:36:45 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_val(t_data *data)
{
	create_map(data);
	map_parser(data);
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		exit_error(data, "Malloc failed.", FAIL);
	set_player(data);
}
