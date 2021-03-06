/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:50:59 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/24 19:36:21 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	check_rest(t_data *data, t_str_node **node)
{
	t_str_node	*curr;
	t_str_node	*last;

	curr = *node;
	last = get_last_str_node(*node);
	while (curr && !curr->map)
	{
		if (!curr->empty)
			exit_error(data, "Map file invalid.", FAILURE);
		curr = curr->next;
	}
	if (!curr)
		exit_error(data, "No map existent.", FAILURE);
	while (!last->map)
	{
		if (!last->empty)
			exit_error(data, "Map file invalid.", FAILURE);
		del_last_node(&curr);
		last = get_last_str_node(curr);
	}
}

static bool	check_map_identifier(t_parser_check *check)
{
	if (!check->n_identifier || !check->e_identifier || !check->s_identifier
		|| !check->w_identifier || !check->c_identifier
		|| !check->f_identifier)
		return (false);
	return (true);
}

void	check_curr_str(t_data *data, char *str)
{
	char	**str_arr;

	str_arr = ft_split_ws(str);
	if (!str_arr)
		exit_error(data, "Malloc failed.", FAILURE);
	if (ft_strlen_arr((const char **) str_arr) != 2)
	{
		ft_free_str_arr(&str_arr);
		exit_error(data, "Map identifier invalid.", FAILURE);
	}
	if (ft_strlen(str_arr[0]) == 2)
		texture_identifier(data, str_arr[0], str_arr[1]);
	else if (ft_strlen(str_arr[0]) == 1)
		color_identifier(data, *str_arr[0], str_arr[1]);
	else
	{
		ft_free_str_arr(&str_arr);
		exit_error(data, "Map identifier invalid.", FAILURE);
	}
	ft_free_str_arr(&str_arr);
}

void	init_parser_check(t_parser_check *check)
{
	check->n_identifier = false;
	check->s_identifier = false;
	check->e_identifier = false;
	check->w_identifier = false;
	check->c_identifier = false;
	check->f_identifier = false;
}

void	parser(t_data *data)
{
	t_str_node	*curr_node;

	init_parser_check(&data->check);
	curr_node = data->file_data;
	data->texture_paths = ft_calloc(5, sizeof(char *));
	if (!data->texture_paths)
		exit_error(data, "Malloc failed.", FAILURE);
	while (!check_map_identifier(&data->check))
	{
		if (curr_node->map && !check_map_identifier(&data->check))
			exit_error(data, "Map cannot be first.", FAILURE);
		if (!curr_node->empty)
			check_curr_str(data, curr_node->str);
		curr_node = curr_node->next;
	}
	check_rest(data, &curr_node);
}
