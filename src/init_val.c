/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:21:55 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/20 19:43:00 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <stdio.h>

static void	set_map_size(t_data *data, t_str_node *node)
{
	int	width;
	int	curr_wid;
	int	height;

	width = 0;
	height = 0;
	while (node)
	{
		curr_wid = ft_strlen(node->str);
		if (node->str[curr_wid - 1] == '\n')
			curr_wid--;
		if (curr_wid > width)
			width = curr_wid;
		height++;
		node = node->next;
	}
	data->map_width = width;
	data->map_height = height;
}

static t_str_node	*get_first_map_str(t_str_node *node)
{
	while (node && !node->map)
		node = node->next;
	return (node);
}

void	create_map(t_data *data)
{
	t_str_node	*map;

	map = get_first_map_str(data->file_data);
	set_map_size(data, map);
	printf("\n%sW: %d, H: %d\n", map->str, data->map_width, data->map_height);
}

void	init_val(t_data *data)
{
	// allocate memory for structs
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		exit(FAIL); //alloc failed

	create_map(data);

	// setting up player starting position
	data->player->pos.x = 5;
	data->player->pos.y = 2;

	data->player->dir.x = 0;
	data->player->dir.y = 1;

	data->player->plane.x = 0.66;
	data->player->plane.y = 0;
}
