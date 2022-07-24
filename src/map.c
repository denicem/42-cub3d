/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 23:59:08 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/24 19:19:36 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	copy_filemap(t_data *data, t_str_node *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map_height && map)
	{
		data->map[y] = ft_calloc(data->map_width + 1, sizeof(char));
		if (!(data->map[y]))
			exit_error(data, "Malloc FAILUREed.", FAILURE);
		x = 0;
		while (x < data->map_width && map->str[x])
		{
			if (ft_isspace(map->str[x]) && map->str[x] != '\n')
				(data->map)[y][x] = '+';
			else if (is_map_char(map->str[x]))
				(data->map)[y][x] = map->str[x];
			x++;
		}
		y++;
		map = map->next;
	}
}

static void	set_map_size(t_data *data, t_str_node *node)
{
	int	width;
	int	curr_wid;
	int	height;

	width = 0;
	height = 0;
	while (node)
	{
		if (node->empty)
			exit_error(data, "Empty line between map.", FAILURE);
		if (!node->map)
			exit_error(data, "Invalid map characters.", FAILURE);
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

void	create_map(t_data *data)
{
	t_str_node	*map;

	map = get_first_map_str(data->file_data);
	set_map_size(data, map);
	data->map = ft_calloc(data->map_height + 1, sizeof(char *));
	if (!data->map)
		exit_error(data, "Malloc FAILUREed.", FAILURE);
	copy_filemap(data, map);
}
