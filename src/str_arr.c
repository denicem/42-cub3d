/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 21:29:46 by dmontema          #+#    #+#             */
/*   Updated: 2022/07/23 22:11:35 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
	new->map = false;
	new->empty = false;
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

void	del_last_node(t_str_node **head)
{
	t_str_node	*last;
	t_str_node	*prev;

	last = *head;
	prev = last;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	if (prev == last)
	{
		free((*head)->str);
		(*head)->str = 0;
		free(*head);
		return ;
	}
	free(last->str);
	last->str = 0;
	free(last);
	prev->next = NULL;
}

void	free_str_node(t_str_node **node)
{
	t_str_node	*curr;
	t_str_node	*next;

	curr = *node;
	while (curr)
	{
		next = curr->next;
		free(curr->str);
		free(curr);
		curr = next;
	}
	free(node);
}
