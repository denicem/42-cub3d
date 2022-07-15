/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 03:39:10 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/15 02:16:59 by dmontema         ###   ########.fr       */
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
}

int render_world()
{
	t_data data;

	// data = get_data();
	data.mlx = mlx_init(WIDTH, HEIGHT, "Hypercub3d", true);
	if (!data.mlx)
		return (1);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	init_val(&data);
	raycast(&data);
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
			printf("%sCorrect!\n%s", GREEN, RESET);
			render_world();
		}
		else if (fd == FILE_NOT_FOUND)
			printf("%sFile not found!\n%s", PURPLE, RESET);
		else if (fd == FILENAME_NOT_CORRECT)
			printf("%sOnly file with a .cub extension allowed!\n%s", RED, RESET);
		close(fd);
	}
	else
		printf("%sWrong number of arguments\n%s./cub3d <path to a map file> [✓]\n%s", RED, GREEN_BG, RESET);
	return (0);
}