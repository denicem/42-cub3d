/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_world_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 01:18:12 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/23 22:11:04 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	get_rgba(t_data *data, int c, int a)
{
	if (c == 1)
		return (data->c_colour.red << 24 | data->c_colour.green << 16
			| data->c_colour.blue << 8 | a);
	else
		return (data->f_colour.red << 24 | data->f_colour.green << 16
			| data->f_colour.blue << 8 | a);
}
