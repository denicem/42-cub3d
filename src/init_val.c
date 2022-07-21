/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:21:55 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/21 21:43:00 by mrojas-e         ###   ########.fr       */
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
	data->n_texture = ft_strdup("textures/plaster15_alt_d.png");
	data->s_texture = ft_strdup("textures/plaster15_alt_d.png");
	data->w_texture = ft_strdup("textures/silent_metall05.png");
	data->e_texture = ft_strdup("textures/silent_metall05.png");
}
