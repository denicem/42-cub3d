/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress_bar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 21:52:50 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/07/08 22:19:44 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	progress_bar(void)
{
	int			i;
	static char	bar[500];
	const char	*lable;
	char		*someonesmom;

	someonesmom = "███████████████████";
	i = 0;
	lable = "|/-\\";
	ft_memset(bar, 0, 102 * sizeof(char));
	printf("\e[0;35m \
               LOADING PLEASE WAIT ...\e[0m\n");
	while (i <= 100)
	{
		if (i % 3 == 0)
			ft_strlcpy(&bar[i], someonesmom, 500);
		printf("\r\e[4;35m\e[40m\e[1;98m%-2s\e[0m\e[36m [%d%%] [%c]", bar,
			i, lable[i % 4]);
		usleep(35000);
		fflush(stdout);
		i ++;
	}
	printf("\n");
}