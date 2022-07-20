/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 19:45:59 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/20 02:15:50 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static bool	line_empty(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (false);
		line++;
	}
	return (true);
}

void	get_data(t_data *data) // TODO: mark lines with only map characters (str map)
{
	char	*line;

	line = get_next_line(data->fd);
	while (line)
	{
		if (line && !line_empty(line))
			append_str_node(&data->file_data, new_str_node(line));
		free(line);
		line = get_next_line(data->fd);
	}
	free(line);
}

void	init_data(t_data *data)
{
	data->fd = file_parser(data->file_path);
	if (data->fd < SUCC)
	{
		if (data->fd == FILE_NOT_FOUND)
			printf("%sError:\nFile not found!\n%s", PURPLE, RESET);
		else if (data->fd == FILENAME_NOT_CORRECT)
			printf("%sError:\nOnly file with a .cub extension allowed!\n%s", RED, RESET);
		close(data->fd);
		exit(FAIL);
	}
	else if (data->fd >= SUCC)
		get_data(data);
	close(data->fd);
}
