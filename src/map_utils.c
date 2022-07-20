/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 23:04:57 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/21 00:09:03 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	is_player_char(int c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (true);
	return (false);
}

bool	is_surround_char(int c)
{
	if (c == '0' || c == '1')
		return (true);
	return (false);
}

bool	is_map_char(int c)
{
	if (is_surround_char(c) || is_player_char(c))
		return (true);
	return (false);
}

bool	is_str_map(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str) && !is_map_char(*str))
			return (false);
		str++;
	}
	return (true);
}

t_str_node	*get_first_map_str(t_str_node *node)
{
	while (node && !node->map)
		node = node->next;
	return (node);
}
