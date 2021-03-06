/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 19:45:59 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/24 22:25:08 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

static bool	check_empty_str_node(t_str_node *node)
{
	while (node)
	{
		if (!node->empty)
			return (false);
		node = node->next;
	}
	return (true);
}

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

static void	set_flag(t_str_node *node)
{
	if (line_empty(node->str))
	{
		node->empty = true;
		return ;
	}
	node->map = is_str_map(node->str);
}

void	get_data(t_data *data)
{
	char		*line;
	t_str_node	*curr_node;

	line = get_next_line(data->fd);
	while (line)
	{
		curr_node = append_str_node(&data->file_data, new_str_node(line));
		set_flag(curr_node);
		free(line);
		line = get_next_line(data->fd);
	}
	free(line);
	if (!data->file_data || check_empty_str_node(data->file_data))
	{
		close(data->fd);
		exit_error(data, "Map file empty.", FAILURE);
	}
}

void	init_data(t_data *data)
{
	data->fd = file_parser(data->file_path);
	if (data->fd < SUCCESS)
	{
		if (data->fd == FILE_NOT_FOUND)
			printf("%sError:\nFile not found!\n%s", PURPLE, RESET);
		else if (data->fd == FILENAME_NOT_CORRECT)
			printf("%sError:\nOnly file with a .cub extension allowed!\n%s",
				RED, RESET);
		close(data->fd);
		exit(FAILURE);
	}
	else if (data->fd >= SUCCESS)
		get_data(data);
	close(data->fd);
}
