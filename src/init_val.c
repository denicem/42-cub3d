/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:21:55 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/21 19:12:34 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_val(t_data *data)
{
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		exit(FAIL);
	create_map(data);
	//parse map
	set_player(data);
	data->s_texture = ft_strdup("textures/bluestone.png");
	data->n_texture = ft_strdup("textures/colorstone.png");
	data->w_texture = ft_strdup("textures/greystone.png");
	data->e_texture = ft_strdup("textures/mossy.png");
}
