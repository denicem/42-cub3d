/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 03:39:10 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/14 20:57:39 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void init_val()
{
	start_pos.x = 5;
	start_pos.y = 2;

	dir.x = 0;
	dir.y = 1;

	plane.x = 0.66;
	plane.y = 0;
}

int render_world()
{
	t_data data;

	data.mlx = mlx_init(WIDTH, HEIGHT, "raycast_dda_prototype", true);
	if (!data.mlx)
		return (1);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	init_val();
	raycast_dda_prototype(data.mlx, data.img);
	// raycast_prototype_2();
	// raycast_prototype_3(data.img);
	mlx_loop_hook(data.mlx, &hook, &data);
	mlx_loop(data.mlx);
	mlx_delete_image(data.mlx, data.img);
	mlx_terminate(data.mlx);
	return (0);
}

int	main(int argc, char *argv[])
{
	int	fd;

	(void) argv;
	if (argc == 2)
	{
		fd = file_parser(argv[1]);
		if (fd >= SUCC)
		{
			printf("\e[35mCorrect!\n");
			render_world();
		}
		else if (fd == FILE_NOT_FOUND)
			printf("\e[31mFile not found!\n\e[0m");
		else if (fd == FILENAME_NOT_CORRECT)
			printf("\e[31mOnly file with a .cub extension allowed!\n\e[0m");
		close(fd);
	}
	else
		printf("\e[31mWrong number of arguments\n\e[42m./cub3d <path to a map file>[✓]\n");
	return (0);
}