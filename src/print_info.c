/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 22:31:55 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/22 19:59:14 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// NOTE: temp file - for debuggin' purposes

void	print_str_node(t_str_node *node)
{
	while (node)
	{
		if (node->map)
			printf("%s", CYAN);
		printf("%s", node->str);
		if (node->map)
			printf("%s", RESET);
		node = node->next;
	}
	printf("\n");
}

void	print_map(t_data *data)
{
	int	i;

	printf("MAP:\n");
	printf("WIDTH: %d, HEIGHT: %d\n\n", data->map_width, data->map_height);
	i = 0;
	while ((data->map)[i])
	{
		printf("%s\n", (data->map)[i]);
		i++;
	}
	printf("\n");
}

void	print_player_info(t_data *data)
{
	printf("PLAYER: starting position\n");
	printf("POS\t[%d %d]\n", (int) data->player->pos.x,
		(int) data->player->pos.y);
	printf("DIR\t[%d %d]\n", (int) data->player->dir.x,
		(int) data->player->dir.y);
	printf("PLANE\t[%.2f %.2f]\n", data->player->plane.x, data->player->plane.y);
}
