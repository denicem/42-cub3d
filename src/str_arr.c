/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_node.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 21:29:46 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/19 21:30:16 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// static bool is_mapchar(int c)
// {
// 	if (c == '0' || c == '1' || c == 'N' || c == 'E' || c == 'S' || c == 'W')
// 		return (true);
// 	return (false);
// }

// static bool is_str_map(char *str)
// {
// 	if (*str || *str == '\n')
// 		return (false);
// 	while (*str)
// 	{
// 		if (!ft_isspace(*str) && !is_mapchar(*str))
// 			return (false);
// 		str++;
// 	}
// 	return (true);
// }

t_str_node	*new_str_node(char *str)
{
	t_str_node	*new;

	new = ft_calloc(1, sizeof(t_str_node));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	if (!(new->str))
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

t_str_node	*get_last_str_node(t_str_node *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

t_str_node	*append_str_node(t_str_node **head, t_str_node *new)
{
	t_str_node	*last;

	if (!(*head))
		*head = new;
	else
	{
		last = get_last_str_node(*head);
		last->next = new;
	}
	return (new);
}

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
