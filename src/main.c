/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 03:39:10 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/15 00:42:05 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// t_data	*get_data()
// {
// 	static t_data data;

// 	return (&data);
// }

void init_val(t_data *data)
{
	// allocate memory for structs
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		exit(FAIL); //alloc failed

	// setting up player starting position
	data->player->pos.x = 5;
	data->player->pos.y = 2;

	data->player->dir.x = 0;
	data->player->dir.y = 1;

	data->player->plane.x = 0.66;
	data->player->plane.y = 0;

	//setting up map
	// data->map_int[0] = {1,1,1,1,1,1,1,1,1,1};
	// data->map_int[1] = {1,1,0,0,0,0,0,0,1,1};
	// data->map_int[2] = {1,0,0,0,0,0,0,0,0,1};
	// data->map_int[3] = {1,0,0,0,0,0,0,0,0,1};
	// data->map_int[4] = {1,0,0,0,0,0,0,0,0,1};
	// data->map_int[5] = {1,1,1,1,0,0,1,1,1,1};
	// data->map_int[6] = {1,0,1,0,0,0,0,1,0,1};
	// data->map_int[7] = {1,0,1,0,0,0,0,1,0,1};
	// data->map_int[8] = {1,0,0,0,0,0,0,0,0,1};
	// data->map_int[9] = {1,1,1,1,1,1,1,1,1,1};
}

int render_world()
{
	t_data data;

	// data = get_data();
	data.mlx = mlx_init(WIDTH, HEIGHT, "raycast_dda_prototype", true);
	if (!data.mlx)
		return (1);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	init_val(&data);
	raycast_dda_prototype(&data);
	mlx_loop_hook(data.mlx, &hook, &data);
	mlx_loop(data.mlx);
	mlx_delete_image(data.mlx, data.img);
	mlx_terminate(data.mlx);
	free(data.player);
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