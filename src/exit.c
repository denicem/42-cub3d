/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:05:35 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/23 22:13:10 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_data(t_data *data)
{
	(void) data;
	// if (data->file_path)
	// 	free(data->file_path);
	// if (data->file_data)
	// 	free_str_node(&data->file_data);
	// if (data->player)
	// 	free(data->player);
	// if (data->map)
	// 	ft_free_str_arr(&data->map);
	// if (data->texture_paths)
	// 	ft_free_str_arr(&data->texture_paths);
}

void	exit_error(t_data *data, char *msg, int error_code)
{
	(void) data;
	printf("%sError:%s\n", RED, RESET);
	if (msg)
		printf("%s%s%s\n", RED, msg, RESET);
	// free data
	exit(error_code);
}
