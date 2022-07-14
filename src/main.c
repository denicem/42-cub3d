/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 03:39:10 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/14 02:50:26 by dmontema         ###   ########.fr       */
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
			printf("Correct!\n");
			render_world();
		}
		else if (fd == FILE_NOT_FOUND)
			printf("File not found!\n");
		else if (fd == FILENAME_NOT_CORRECT)
			printf("Only file with a .cub extension allowed!\n");
		close(fd);
	}
	else
		printf("Wrong number of arguments\n./cub3d <path to a map file>\n");
	return (0);
}