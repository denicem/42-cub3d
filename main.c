/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 03:39:10 by dmontema          #+#    #+#             */
/*   Updated: 2022/06/28 03:39:10 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	main(int argc, char *argv[])
{
	(void) argv;
	if (argc == 2)
	{
		// if (strnstr(argv[1], ".cub", strlen(argv[1])))
		// {
		// 	printf("Right file\n");
		// }
		// else
		// {
		// 	printf("Only files with .cub extension allowed.\n");
		// }
	}
	else
	{
		printf("Wrong number of arguments\n");
	}
	return (0);
}
